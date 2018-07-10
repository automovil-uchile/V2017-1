# -*- coding: utf-8 -*-

import numpy as np

class Motor(object):
    
    def __init__(self, l, w):
        self.vel = 0
        self.l = l
        self.w = w

    def get_vel(self):
        return self.vel

    def set_vel(self, v, ang):
        return

class MotorIzquierdo(Motor):

    def __init__(self , l, w):
        Motor.__init__(self, l, w)

    #Override
    def set_vel(self, v, ang):
        ang = ang*np.pi/180
        a = self.l/(np.tan(ang) + 1e-5)
        self.vel = v*(1 - self.w/2/a)

class MotorDerecho(Motor):

    def __init__(self , l, w):
        Motor.__init__(self, l, w)

    #Override
    def set_vel(self, v, ang):
        ang = ang*np.pi/180
        a = self.l/(np.tan(ang) + 1e-5)
        self.vel = v*(1 + self.w/2/a)

