# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

u_data = np.loadtxt( "punto1bdm.txt" )

fig = plt.figure(); ax = fig.gca()

x = np.linspace( 0 , 2.0 , 100)

u, = plt.plot( x , u_data[0] )

def inicio():
    ax.set_xlim( 0 , 2 )
    ax.set_xlabel( u"Posición (unidades arbitrarias)" )
    ax.set_ylabel( "Temperatura (unidades arbitrarias)" )

def paso(i):
    u.set_data( x , u_data[i] )

anim = FuncAnimation( fig , paso , np.arange( 0 , 500 ) , init_func = inicio )

anim.save("heat.gif" , writer = PillowWriter(fps=20) )
