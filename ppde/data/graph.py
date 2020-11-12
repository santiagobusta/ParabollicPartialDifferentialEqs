# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt

rmsefdm_t = np.loadtxt( "rmsefdm.txt" )
rmsebdm_t = np.loadtxt( "rmsebdm.txt" )
rmsecn_t = np.loadtxt( "rmsecn.txt" )

rmsefdm_Nt = np.loadtxt( "rmsefdm_Nt.txt" )
rmsebdm_Nt = np.loadtxt( "rmsebdm_Nt.txt" )
rmsecn_Nt = np.loadtxt( "rmsecn_Nt.txt" )

t = np.linspace( 0 , 0.1 , 101)
Nt = np.arange( 0 , 999 )

fig = plt.figure( figsize = (10 , 5) ); ax = fig.gca()
ax.plot( t , rmsefdm_t , linewidth = 2 , label = 'FD' )
ax.plot( t , rmsebdm_t , linewidth = 2 , label = 'BD' )
ax.plot( t , rmsecn_t , linewidth = 2 , label = 'CN' )
ax.set_yscale('log')
ax.set_xlabel("Tiempo (unidades arbitrarias)")
ax.set_ylabel("RMSE")
ax.grid( True )
ax.legend()
plt.savefig("rmse_t.png")

fig = plt.figure( figsize = (10 , 5) ); ax = fig.gca()
ax.plot( Nt , rmsefdm_Nt , linewidth = 2 , label = 'FD' )
ax.plot( Nt , rmsebdm_Nt , linewidth = 2 , label = 'BD' )
ax.plot( Nt , rmsecn_Nt , linewidth = 2 , label = 'CN' )
ax.set_yscale('log')
ax.set_xlabel(u"Número de pasos temporales")
ax.set_ylabel("RMSE")
ax.grid( True )
ax.legend()
plt.savefig("rmse_Nt.png")
