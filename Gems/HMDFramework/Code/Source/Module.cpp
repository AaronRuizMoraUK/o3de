/*
 * Copyright (c) Contributors to the Open 3D Engine Project. For complete copyright and license terms please see the LICENSE at the root of this distribution.
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>

//#include <AzFramework/Metrics/MetricsPlainTextNameRegistration.h>

#include <HMDDebuggerComponent.h>
#include <HMDLuaComponent.h>

#ifdef VR_EDITOR
#include <EditorVRPreviewComponent.h>
#endif // VR_EDITOR

namespace HMDFramework
{
    class Module
        : public AZ::Module
    {
    public:
        AZ_RTTI(Module, "{57CFF7A2-A9D0-4D30-912E-4564C4DF19D3}", AZ::Module);
        AZ_CLASS_ALLOCATOR(Module, AZ::SystemAllocator, 0);

        Module()
            : AZ::Module()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            m_descriptors.insert(m_descriptors.end(), 
            {
                HMDDebuggerComponent::CreateDescriptor(),
                AZ::VR::HMDLuaComponent::CreateDescriptor(),
#ifdef VR_EDITOR
                AZ::VR::EditorVRPreviewComponent::CreateDescriptor(),
#endif //VR_EDITOR
            });

			/*
            // This is an internal Amazon gem, so register it's components for metrics tracking, otherwise the name of the component won't get sent back.
            // IF YOU ARE A THIRDPARTY WRITING A GEM, DO NOT REGISTER YOUR COMPONENTS WITH EditorMetricsComponentRegistrationBus
            AZStd::vector<AZ::Uuid> typeIds;
            typeIds.reserve(m_descriptors.size());
            for (AZ::ComponentDescriptor* descriptor : m_descriptors)
            {
                typeIds.emplace_back(descriptor->GetUuid());
            }
            EBUS_EVENT(AzFramework::MetricsPlainTextNameRegistrationBus, RegisterForNameSending, typeIds);
			*/
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList
            {
                azrtti_typeid<HMDDebuggerComponent>(),
                azrtti_typeid<AZ::VR::HMDLuaComponent>(),
            };
        }
    };
}

// DO NOT MODIFY THIS LINE UNLESS YOU RENAME THE GEM
// The first parameter should be GemName_GemIdLower
// The second should be the fully qualified name of the class above
AZ_DECLARE_MODULE_CLASS(Gem_HMDFramework, HMDFramework::Module)
