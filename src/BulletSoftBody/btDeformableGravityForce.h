/*
 Written by Xuchen Han <xuchenhan2015@u.northwestern.edu>
 
 Bullet Continuous Collision Detection and Physics Library
 Copyright (c) 2019 Google Inc. http://bulletphysics.org
 This software is provided 'as-is', without any express or implied warranty.
 In no event will the authors be held liable for any damages arising from the use of this software.
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it freely,
 subject to the following restrictions:
 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef BT_DEFORMABLE_GRAVITY_FORCE_H
#define BT_DEFORMABLE_GRAVITY_FORCE_H

#include "btDeformableLagrangianForce.h"

class btDeformableGravityForce : public btDeformableLagrangianForce
{
public:
    typedef btAlignedObjectArray<btVector3> TVStack;
    btVector3 m_gravity;
    
    btDeformableGravityForce(const btVector3& g) : m_gravity(g)
    {
    }
    
    virtual void addScaledImplicitForce(btScalar scale, TVStack& force)
    {
    }
    
    virtual void addScaledExplicitForce(btScalar scale, TVStack& force)
    {
        addScaledGravityForce(scale, force);
    }
    
    virtual void addScaledForceDifferential(btScalar scale, const TVStack& dv, TVStack& df)
    {
        
    }
    
    virtual void addScaledGravityForce(btScalar scale, TVStack& force)
    {
        int numNodes = getNumNodes();
        btAssert(numNodes <= force.size())
        for (int i = 0; i < m_softBodies.size(); ++i)
        {
            btSoftBody* psb = m_softBodies[i];
            for (int j = 0; j < psb->m_nodes.size(); ++j)
            {
                btSoftBody::Node& n = psb->m_nodes[j];
                size_t id = n.index;
                btScalar mass = (n.m_im == 0) ? 0 : 1. / n.m_im;
                btVector3 scaled_force = scale * m_gravity * mass;
                force[id] += scaled_force;
            }
        }
    }
    
    virtual btDeformableLagrangianForceType getForceType()
    {
        return BT_GRAVITY_FORCE;
    }
    
    
};
#endif /* BT_DEFORMABLE_GRAVITY_FORCE_H */
