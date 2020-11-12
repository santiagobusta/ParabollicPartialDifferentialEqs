import numpy as np
import matplotlib.pyplot as plt

rmsefdm_t = np.loadtxt( "rmsefdm.txt" )
rmsebdm_t = np.loadtxt( "rmsebdm.txt" )
rmsecn_t = np.loadtxt( "rmsecn.txt" )

print rmsefdm_t


t = np.linspace( 0 , 0.1 , 101)

fig = plt.figure(); ax = fig.gca()
ax.plot( t , rmsefdm_t , 's-' , label = 'FWD' )
ax.plot( t , rmsebdm_t , 's-' , label = 'BWD' )
ax.plot( t , rmsecn_t , 's-' , label = 'CN' )
ax.grid( True )
ax.legend()
plt.savefig("rmse_t.png")
