/*
 * Copyright (c) Contributors to the Open 3D Engine Project. For complete copyright and license terms please see the LICENSE at the root of
 * this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

/*
* This is a bus for interfacing with any available VR controllers. Most 
* VR controllers will connect to this bus when their respective HMDs have 
* been initialized but that's not always the case. PSVR supports
* controller systems that can be used without any HMD. We still want to get
* tracking information about these controllers even if we're not rendering in VR. 
*/

#pragma once

#include <AzCore/EBus/EBus.h>
#include <VRCommon.h>

namespace AZ 
{
    namespace VR 
    {
        class ControllerBus 
            : public AZ::EBusTraits
        {
        public:
            virtual ~ControllerBus() {}

            //////////////////////////////////////////////////////////////////////////
            // EBusTraits overrides
            static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
            static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
            //////////////////////////////////////////////////////////////////////////

            virtual TrackingState* GetTrackingState([[maybe_unused]] ControllerIndex controllerIndex) { return nullptr; }
        
            virtual bool IsConnected([[maybe_unused]] ControllerIndex controllerIndex) { return false; }
        };    

        using ControllerRequestBus = AZ::EBus<ControllerBus>;
    }//namespace VR
}//namespace AZ
