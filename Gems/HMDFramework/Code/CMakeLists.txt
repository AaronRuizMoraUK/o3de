#
# Copyright (c) Contributors to the Open 3D Engine Project. For complete copyright and license terms please see the LICENSE at the root of this distribution.
# 
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

ly_get_list_relative_pal_filename(pal_dir ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME})

include(${pal_dir}/PAL_${PAL_PLATFORM_NAME_LOWERCASE}.cmake) #for PAL_TRAIT_HMDFRAMEWORK Traits

if(PAL_TRAIT_HMDFRAMEWORK_USE_STUB)
    include(hmdframework_stub.cmake)
    return()
endif()

ly_add_target(
    NAME HMDFramework.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        hmdframework_files.cmake
    INCLUDE_DIRECTORIES
        PRIVATE
            Source
    BUILD_DEPENDENCIES
        PUBLIC
            AZ::AzCore
)

ly_add_target(
    NAME HMDFramework ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        hmdframework_shared_files.cmake
    INCLUDE_DIRECTORIES
        PRIVATE
            Source
    BUILD_DEPENDENCIES
        PRIVATE
            Gem::HMDFramework.Static
)

# use the HMDFramework module in clients and servers:
ly_create_alias(NAME HMDFramework.Clients NAMESPACE Gem TARGETS Gem::HMDFramework)
ly_create_alias(NAME HMDFramework.Servers NAMESPACE Gem TARGETS Gem::HMDFramework)

if(PAL_TRAIT_BUILD_HOST_TOOLS)
    ly_add_target(
        NAME HMDFramework.Editor.Static STATIC
        NAMESPACE Gem
        AUTOMOC
        FILES_CMAKE
            hmdframework_editor_files.cmake
        INCLUDE_DIRECTORIES
            PRIVATE
                Source
        COMPILE_DEFINITIONS
            PRIVATE
                VR_EDITOR
        BUILD_DEPENDENCIES
            PUBLIC
                Gem::HMDFramework.Static
    )

    ly_add_target(
        NAME HMDFramework.Editor GEM_MODULE
        NAMESPACE Gem
        FILES_CMAKE
            hmdframework_editor_shared_files.cmake
        INCLUDE_DIRECTORIES
            PRIVATE
                Source
        COMPILE_DEFINITIONS
            PRIVATE
                VR_EDITOR
        BUILD_DEPENDENCIES
            PRIVATE
                Gem::HMDFramework.Editor.Static
    )

    # use the HMDFramework.Editor module in dev tools:
    ly_create_alias(NAME HMDFramework.Builders NAMESPACE Gem TARGETS Gem::HMDFramework.Editor)
    ly_create_alias(NAME HMDFramework.Tools    NAMESPACE Gem TARGETS Gem::HMDFramework.Editor)
endif()
