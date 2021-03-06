/*
Highly Optimized Object-oriented Many-particle Dynamics -- Blue Edition
(HOOMD-blue) Open Source Software License Copyright 2008, 2009 Ames Laboratory
Iowa State University and The Regents of the University of Michigan All rights
reserved.

HOOMD-blue may contain modifications ("Contributions") provided, and to which
copyright is held, by various Contributors who have granted The Regents of the
University of Michigan the right to modify and/or distribute such Contributions.

Redistribution and use of HOOMD-blue, in source and binary forms, with or
without modification, are permitted, provided that the following conditions are
met:

* Redistributions of source code must retain the above copyright notice, this
list of conditions, and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
list of conditions, and the following disclaimer in the documentation and/or
other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of HOOMD-blue's
contributors may be used to endorse or promote products derived from this
software without specific prior written permission.

Disclaimer

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND/OR
ANY WARRANTIES THAT THIS SOFTWARE IS FREE OF INFRINGEMENT ARE DISCLAIMED.

IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Maintainer: jglaser

#include <boost/shared_ptr.hpp>
#include <boost/python.hpp>
#include <hoomd/hoomd.h>

/*! \file OrderingExternal.h
    \brief Declares a class for computing an external force field
*/

#ifdef NVCC
#error This header cannot be compiled by nvcc
#endif

#ifndef __ORDERING_EXTERNAL_H__
#define __ORDERING_EXTERNAL_H__

//! Applys a constraint force to keep a group of particles on a sphere
/*! \ingroup computes
*/
class OrderingExternal: public ForceCompute
    {
    public:
        //! Constructs the compute
        OrderingExternal(boost::shared_ptr<SystemDefinition> sysdef, std::vector<Scalar> order_parameters, 
                         std::vector<int3> lattice_vectors, std::vector<Scalar> phases, Scalar interface_width, std::string log_suffix);

        //! Sets parameters of the evaluator
        void setParams(unsigned int type, Scalar order_parameter);

        //! Returns a list of log quantities this compute calculates
        virtual std::vector< std::string > getProvidedLogQuantities();

        //! Calculates the requested log value and returns it
        virtual Scalar getLogValue(const std::string& quantity, unsigned int timestep);

    protected:

        GPUArray<Scalar> m_order_parameters;      //!< Array of per-type parameters
        GPUArray<int3> m_lattice_vectors;         //!< Array of lattice vectors
        GPUArray<Scalar> m_phases;                //!< Array of phases
        Scalar m_interface_width;                 //!< Interface width
        std::string m_log_name;                   //!< Cached log name

        //! Actually compute the forces
        virtual void computeForces(unsigned int timestep);

    };

inline bool operator== (const int3 &a, const int3 &b)
    {
    return (a.x == b.x &&
            a.y == b.y &&
            a.z == b.z);
    }

void export_OrderingExternal();
#endif

