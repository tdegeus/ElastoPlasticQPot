
import ElastoPlasticQPot.Cartesian2d as GMat
import numpy as np

# ==================================================================================================

def EQ(a,b):
  if np.abs(a-b) > 1.e-12:
    raise IOError('Failed: {0:f} != {1:f}'.format(a,b))

# ==================================================================================================

# material model
# - parameters
K = 12.3
G = 45.6
# - model
mat = GMat.Elastic(K,G)

# simple shear + volumetric deformation
# - parameters
gamma = 0.02
epsm  = 0.12
# - strain
Eps = [[ epsm  , gamma],
       [ gamma , epsm ]]
# - stress
Sig = mat.Sig(Eps)
# - analytical solution
EQ( Sig[0,0], K * epsm  )
EQ( Sig[1,1], K * epsm  )
EQ( Sig[0,1], G * gamma )
# - plastic strain
EQ( mat.epsp(Eps), 0 )
# - yield strain index
EQ( mat.find(Eps), 0 )

# ==================================================================================================

# material model
# - parameters
K = 12.3
G = 45.6
# - model
mat = GMat.Cusp(K,G,[0.01, 0.03, 0.10])

# simple shear + volumetric deformation
# - parameters
gamma = 0.02
epsm  = 0.12
# - strain
Eps = [[ epsm  , gamma],
       [ gamma , epsm ]]
# - stress
Sig = mat.Sig(Eps)
# - analytical solution
EQ( Sig[0,0], K * epsm )
EQ( Sig[1,1], K * epsm )
EQ( Sig[0,1], G * 0.   )
# - plastic strain
EQ( mat.epsp(Eps), 0.02 )
# - yield strain index
EQ( mat.find(Eps), 1 )

# ==================================================================================================

# material model
# - parameters
K = 12.3
G = 45.6
# - model
mat = GMat.Smooth(K,G,[0.01, 0.03, 0.10])

# simple shear + volumetric deformation
# - parameters
gamma = 0.02
epsm  = 0.12
# - strain
Eps = [[ epsm  , gamma],
       [ gamma , epsm ]]
# - stress
Sig = mat.Sig(Eps)
# - analytical solution
EQ( Sig[0,0], K * epsm )
EQ( Sig[1,1], K * epsm )
EQ( Sig[0,1], G * 0.   )
# - plastic strain
EQ( mat.epsp(Eps), 0.02 )
# - yield strain index
EQ( mat.find(Eps), 1 )

# ==================================================================================================

# parameters
K = 12.3
G = 45.6

# allocate matrix
mat = GMat.Matrix([3,2])

# row 0: elastic
k = [K, K]
g = [G, G]

index = [[0,0],
         [0,1]]

mat.addElastic(index,k,g)

# row 1: cups
k    = [K, K]
g    = [G, G]
epsy = [[0.01,0.03,0.10],
        [0.01,0.03,0.10]]

index = [[1,0],
         [1,1]]

mat.addCusp(index,k,g,epsy)

# row 2: smooth
k    = [K, K]
g    = [G, G]
epsy = [[0.01,0.03,0.10],
        [0.01,0.03,0.10]]

index = [[2,0],
         [2,1]]

mat.addSmooth(index,k,g,epsy)

# simple shear + volumetric deformation
# - parameters
gamma = 0.02;
epsm  = 0.12;
# - strain
Eps        = np.zeros((3,2,3))
Eps[:,:,0] = epsm
Eps[:,:,1] = gamma
Eps[:,:,2] = epsm
# - stress & plastic strain
Sig  = mat.Sig (Eps)
epsp = mat.epsp(Eps)

# - analytical solution
EQ( Sig[0,0,0], K * epsm ); EQ( Sig[0,1,0], K * epsm )
EQ( Sig[0,0,2], K * epsm ); EQ( Sig[0,1,2], K * epsm )
EQ( Sig[0,0,1], G * gamma); EQ( Sig[0,1,1], G * gamma)
EQ( Sig[1,0,0], K * epsm ); EQ( Sig[1,1,0], K * epsm )
EQ( Sig[1,0,2], K * epsm ); EQ( Sig[1,1,2], K * epsm )
EQ( Sig[1,0,1], G * 0.   ); EQ( Sig[1,1,1], G * 0.   )
EQ( Sig[2,0,0], K * epsm ); EQ( Sig[2,1,0], K * epsm )
EQ( Sig[2,0,2], K * epsm ); EQ( Sig[2,1,2], K * epsm )
EQ( Sig[2,0,1], G * 0.   ); EQ( Sig[2,1,1], G * 0.   )
# - plastic strain
EQ( epsp[0,0], 0    ); EQ( epsp[0,1], 0    )
EQ( epsp[1,0], gamma); EQ( epsp[1,1], gamma)
EQ( epsp[2,0], gamma); EQ( epsp[2,1], gamma)