/*!
 * \file wall_model.hpp
 * \brief Headers for the wall model functions for hom large eddy simulations.
 * \author E. van der Weide, T. Economon, P. Urbanczyk
 * \version 5.0.0 "Raven"
 *
 * SU2 Lead Developers: Dr. Francisco Palacios (Francisco.D.Palacios@boeing.com).
 *                      Dr. Thomas D. Economon (economon@stanford.edu).
 *
 * SU2 Developers: Prof. Juan J. Alonso's group at Stanford University.
 *                 Prof. Piero Colonna's group at Delft University of Technology.
 *                 Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *                 Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *                 Prof. Rafael Palacios' group at Imperial College London.
 *                 Prof. Edwin van der Weide's group at the University of Twente.
 *                 Prof. Vincent Terrapon's group at the University of Liege.
 *
 * Copyright (C) 2012-2017 SU2, the open-source CFD code.
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "../../Common/include/mpi_structure.hpp"
#include "../../Common/include/config_structure.hpp"
#include "../../Common/include/fem_geometry_structure.hpp"

#include <iostream>
#include <cmath>

using namespace std;

// Forward declaration of class CSolver avoids circular dependency
class CSolver;

/*!
 * \class CSGSModel
 * \brief Base class for defining the LES subgrid scale model.
 * \author: E. van der Weide, T. Economon, P. Urbanczyk
 * \version 5.0.0 "Raven"
 */
class CWallModel {

public:

  /*!
   * \brief Constructor of the class.
   */
  CWallModel(void);

  /*!
   * \brief Destructor of the class.
   */
  virtual ~CWallModel(void);

  virtual void ComputeWallShear();

  virtual void ComputeWallHeatFlux();

  virtual void Initialize(CBoundaryFEM * boundary, CConfig *config, CGeometry *geometry);

  virtual void SetUpExchange(CBoundaryFEM * boundary, CConfig *config, CGeometry *geometry);

  virtual void SetPoints(CSurfaceElementFEM * thisElem, vector<su2double> exchangeCoords);

protected:

  su2double thickness; /*!< \brief The thickness of the wall model. This is also basically the exchange location */

};

class CWallModel1DEQ : public CWallModel {

public:

  /*!
   * \brief Constructor of the class.
   */
  CWallModel1DEQ(void);

  /*!
   * \brief Destructor of the class.
   */
  ~CWallModel1DEQ(void);

  void ComputeWallShear();

  void ComputeWallHeatFlux();

  void Initialize(CBoundaryFEM * boundary, CConfig *config, CGeometry *geometry);

  void SetUpExchange(CBoundaryFEM * boundary, CConfig *config, CGeometry *geometry);

  void SetPoints(CSurfaceElementFEM * thisElem, vector<su2double> exchangeCoords);

  void SolveCoupledSystem(CSurfaceElementFEM * thisElem, su2double u_bc, su2double T_bc, su2double P_bc, su2double * wallShear, su2double * heatFlux);

  void GetExchangeValues(unsigned short intPointID, su2double * u_exchange, su2double * T_exchange,  su2double * P_exchange);

protected:

  su2double expansionRatio;
  unsigned short int numPoints;
  bool initCondExists;
  su2double tauWallInit;

};
