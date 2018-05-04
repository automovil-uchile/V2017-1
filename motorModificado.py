# -*- coding: utf-8 -*-

import numpy as np

class Motor(object):
    MotCount = 0
    
    def __init__(self, pos, l, w):
        Motor.MotCount += 1
        self.vel = 0
        self.pos = pos
        self.l = l
        self.w = w

    def get_vel(self):
        return self.vel

    def set_vel(self, v, ang):
        return

class MotorIzquierdo(Motor):

    def __init__(self , l, w):
        Motor.__init__(self, "izq", l, w)

    #Override
    def set_vel(self, v, ang):
        ang = ang*np.pi/180
        a = self.l/(np.tan(ang) + 1e-5)
        self.vel = v*(1 - self.w/2/a)

class MotorDerecho(Motor):

    def __init__(self , l, w):
        Motor.__init__(self, "der", l, w)

    #Override
    def set_vel(self, v, ang):
        ang = ang*np.pi/180
        a = self.l/(np.tan(ang) + 1e-5)
        self.vel = v*(1 + self.w/2/a)


if __name__ == "__main__":
        l = 1
        w = 2
        motor_izq = MotorIzquierdo(l,w)
        motor_der = MotorDerecho(l,w)
        print "Velocidad motor derecho"
        print motor_der.get_vel()
        print "Velocidad motor izquierdo"
        vel = motor_izq.get_vel()
        print vel
