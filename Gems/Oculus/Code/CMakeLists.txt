#
# Copyright (c) Contributors to the Open 3D Engine Project. For complete copyright and license terms please see the LICENSE at the root of this distribution.
# 
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

ly_get_list_relative_pal_filename(pal_dir ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME})

include(${pal_dir}/PAL_${PAL_PLATFORM_NAME_LOWERCASE}.cmake) #for PAL_TRAIT_OCULUS Traits

if(PAL_TRAIT_OCULUS_USE_STUB)
    include(oculus_stub.cmake)
    return()
endif()

ly_add_target(
    NAME Oculus.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        oculus_files.cmake
    INCLUDE_DIRECTORIES
        PRIVATE
            Include
            Source
    BUILD_DEPENDENCIES
        PUBLIC
            AZ::AzCore
)

ly_add_target(
    NAME Oculus ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        oculus_shared_files.cmake
    INCLUDE_DIRECTORIES
        PRIVATE
            Include
            Source
    BUILD_DEPENDENCIES
        PRIVATE
            Gem::Oculus.Static
)

# use the Oculus module in clients and servers:
ly_create_alias(NAME Oculus.Clients NAMESPACE Gem TARGETS Gem::Oculus)
ly_create_alias(NAME Oculus.Servers NAMESPACE Gem TARGETS Gem::Oculus)
