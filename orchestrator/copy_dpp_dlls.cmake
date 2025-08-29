# Copy DLLs from a DPP-provided win32 folder (if present) into the target dir
# Expects variables: src_dir (input dir), dst_dir (output dir)

if(EXISTS "${src_dir}")
    file(GLOB _dlls
        "${src_dir}/*.dll"
        "${src_dir}/x64/*.dll"
        "${src_dir}/x86/*.dll"
        "${src_dir}/lib/*.dll"
        "${src_dir}/bin/*.dll"
    )
    foreach(_dll IN LISTS _dlls)
        if(EXISTS "${_dll}")
            execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${_dll}" "${dst_dir}")
        endif()
    endforeach()
endif()
