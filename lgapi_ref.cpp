#pragma once 

#include "lgapi.h"
#include <memory>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void ExitProgram();

struct BatchRenderGL : public IBatchRender
{
  ~BatchRenderGL() override { ExitProgram(); }

  void Render(PipelineStateObject a_state, Geom a_geom, FrameBuffer fb) override;
};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

Display              *dpy;
Window               root, win;
GLint                att[]   = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo          *vi;
GLXContext           glc;
Colormap             cmap;
XSetWindowAttributes swa;
XWindowAttributes	   wa;
XEvent			         xev;

void CreateWindow(int WIN_WIDTH_INITIAL, int WIN_HEIGHT_INITIAL)
{
  if((dpy = XOpenDisplay(NULL)) == NULL)
  {
    printf("\n\tcannot connect to x server\n\n");
    exit(0);
  }

  root = DefaultRootWindow(dpy);

  if((vi = glXChooseVisual(dpy, 0, att)) == NULL)
  {
    printf("\n\tno matching visual\n\n");
    exit(0);
  }

  if((cmap = XCreateColormap(dpy, root, vi->visual, AllocNone)) == 0)
  {
    printf("\n\tcannot create colormap\n\n");
    exit(0);
  }

  swa.event_mask = KeyPressMask;
  swa.colormap 	= cmap;
  win = XCreateWindow(dpy, root, 0, 0, WIN_WIDTH_INITIAL, WIN_HEIGHT_INITIAL, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
  XStoreName(dpy, win, "OpenGL Animation");
  XMapWindow(dpy, win);
}

void SetupGL()
{
  char		font_string[128];
  XFontStruct	*font_struct;

  glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);

  if(glc == NULL)
  {
    printf("\n\tcannot create gl context\n\n");
    exit(0);
  }

  glXMakeCurrent(dpy, win, glc);
  glClearColor(0.00, 0.00, 0.40, 1.00);
}

void ExitProgram()
{
  glXMakeCurrent(dpy, None, NULL);
  glXDestroyContext(dpy, glc);
  XDestroyWindow(dpy, win);
  XCloseDisplay(dpy);
  exit(0);
}


std::shared_ptr<IBatchRender> MakeReferenceImpl() 
{ 
  CreateWindow(512,512);
  SetupGL();

  XGetWindowAttributes(dpy, win, &wa);
  glViewport(0, 0, wa.width, wa.height);

  return std::make_shared<BatchRenderGL>(); 
};

void transposeMatrix(const float in_matrix[16], float out_matrix[16])
{
  for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
      out_matrix[i*4+j] = in_matrix[j*4+i];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BatchRenderGL::Render(PipelineStateObject a_state, Geom a_geom, FrameBuffer fb)
{
  glViewport(0, 0, fb.width, fb.height);

  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

  float tempMat[16];  
  glMatrixMode(GL_PROJECTION);
  transposeMatrix(a_state.projMatrix, tempMat);      // GL assume col-major matrices (which is usually better), while in our API thet are row-major
  glLoadMatrixf(tempMat);

  glMatrixMode(GL_MODELVIEW);
  transposeMatrix(a_state.worldViewMatrix, tempMat); // GL assume col-major matrices (which is usually better), while in our API thet are row-major
  glLoadMatrixf(tempMat);

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);

  glColorPointer (4, GL_FLOAT, 0,  a_geom.vcol4f);
  glVertexPointer(4, GL_FLOAT, 0,  a_geom.vpos4f);
  glDrawArrays   (GL_TRIANGLES, 0, a_geom.primsNum*3);

  glFlush();
  glReadPixels(0, 0, fb.width, fb.height, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)fb.data);
}