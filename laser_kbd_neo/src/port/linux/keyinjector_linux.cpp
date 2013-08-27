/*                                                                              
 * Copyright (C) 2013 Deepin, Inc.                                                 
 *               2013 Leslie Zhai                                                  
 *                                                                              
 * Author:     Leslie Zhai <zhaixiang@linuxdeepin.com>                           
 * Maintainer: Leslie Zhai <zhaixiang@linuxdeepin.com>                           
 *                                                                              
 * This program is free software: you can redistribute it and/or modify         
 * it under the terms of the GNU General Public License as published by         
 * the Free Software Foundation, either version 3 of the License, or            
 * any later version.                                                           
 *                                                                              
 * This program is distributed in the hope that it will be useful,              
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
 * GNU General Public License for more details.                                 
 *                                                                              
 * You should have received a copy of the GNU General Public License            
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        
 */

#include "common.h"
#include "port/common/keyinjector.h"
#include "config_mgr.h"

extern ConfigBundle         g_config_bundle;

class OSKeyInjector_Linux : public OSKeyInjector
{
public :
    OSKeyInjector_Linux() 
    {
    }

    virtual ~OSKeyInjector_Linux() 
    {
    }


    virtual bool injectKeyEvents( const std::vector<KeyEventDesc> & intputlist)
    {
        return true;
    }
};

OSKeyInjector* OSKeyInjector::g_inst = NULL;
static pthread_mutex_t m_mutex = PTHREAD_MUTEX_INITIALIZER;

OSKeyInjector * OSKeyInjector::GetInstance() {
    pthread_mutex_lock(&m_mutex);
    if (OSKeyInjector::g_inst) 
    {
        pthread_mutex_unlock(&m_mutex);
        return OSKeyInjector::g_inst;
    }

    OSKeyInjector::g_inst = new OSKeyInjector_Linux();
    pthread_mutex_unlock(&m_mutex);
    return OSKeyInjector::g_inst;
}


void OSKeyInjector::ReleaseInstance()
{
    pthread_mutex_lock(&m_mutex);
    if (OSKeyInjector::g_inst) 
    {
        delete OSKeyInjector::g_inst;
        OSKeyInjector::g_inst = NULL;
    }
    pthread_mutex_unlock(&m_mutex);
}
