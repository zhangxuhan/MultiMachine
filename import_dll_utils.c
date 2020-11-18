/* This is a simple example of a code that loads an AMESim DLL (shared library)
   created for cosimulation and use this DLL for doing some simple simulation.
   Author: Arne Jansson (jansson@amesim.com)
   Date of last change: Jan 30 2006
   COPYRIGHT 2006 IMAGINE SA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
   #include <dlfcn.h>
#else
   #include <windows.h> 
#endif

#ifdef HPUX
   #include <dl.h>
#endif

#include <string.h>

#include "import_dll_utils.h"


void * FindInLib(void *handle, char *objname)
{
   void *ptrobj;
#ifdef HPUX
   shl_t h = (shl_t)handle;
   if(shl_findsym(&h, objname, TYPE_UNDEFINED, (void *)&ptrobj))
   {
      fprintf(stdout,"FindInLib %s: %s\n",objname, strerror(errno));
      return NULL;
   }
#else
#ifndef WIN32
   ptrobj = dlsym(handle, objname);
   if (ptrobj == NULL)
   {
      fprintf(stdout,"FindInLib %s: %s\n",objname, dlerror());
      return NULL;
   }
#else
   ptrobj = (void(*)())GetProcAddress(handle, objname);
   if (ptrobj == NULL)
   {
      fprintf(stdout,"%s: %s\n",objname, "not found.");
      return NULL;
   }
#endif
#endif
   return ptrobj;
}

/**
 * load AMESim model shared library: Makes functions from the shared library
 * available through an AME_DLL structure.
 * Note that AME_DLL structure it self is not allocated in this function
 * \sa unloadamesimdll
 * \param libname path to the shared library to load
 * \param amedll pointer to the AME_DLL structure
 * \return 1 on success, 0 if an error occurred.
 */
int loadamesimdll(char *libname, AME_DLL *amedll)
{

#ifdef HPUX
   amedll->handle = (void *)shl_load(libname, BIND_NONFATAL | BIND_DEFERRED, 0);
   if (amedll->handle == NULL)
   {
      fprintf(stdout,"OpenDynLib %s: %s\n",libname, strerror(errno));
      return 0;
   }
#else
#ifndef WIN32
   amedll->handle = dlopen(libname, RTLD_NOW);
   if (amedll->handle == NULL)
   {
      fprintf(stdout,"OpenDynLib %s: %s\n",libname, dlerror());
      return 0;
   }
#else
   amedll->handle = LoadLibrary(libname);
   if (amedll->handle == NULL)
   {
      fprintf(stdout,"%s: %s\n",libname, "not loaded.");
      return 0;
   }
#endif
#endif

   /* Then lookup the entrypoints that we want to call using GetProcAddress */
   amedll->AMEInitSizes = FindInLib(amedll->handle, "AMEInitSizes");
   if (amedll->AMEInitSizes  == NULL)
   {
      fprintf(stdout,"AMEInitSizes not found.\n");
      return 0;
   }
   amedll->AMEInitModel = FindInLib(amedll->handle, "AMEInitModel");
   if (amedll->AMEInitModel  == NULL)
   {
      fprintf(stdout,"AMEInitModel not found.\n");
      return 0;
   }
   amedll->AMEdoAStep = FindInLib(amedll->handle, "AMEdoAStep");
   if (amedll->AMEdoAStep  == NULL)
   {
      fprintf(stdout,"AMEdoAStep not found.\n");
      return 0;
   }
   amedll->AMEdoAStep2 = FindInLib(amedll->handle, "AMEdoAStep2");
   if (amedll->AMEdoAStep2  == NULL)
   {
      fprintf(stdout,"AMEdoAStep2 not found.\n");
      return 0;
   }
   amedll->AMEInputs = FindInLib(amedll->handle, "AMEInputs");
   if (amedll->AMEInputs  == NULL)
   {
      fprintf(stdout,"AMEInputs not found.\n");
      return 0;
   }
   amedll->AMEOutputs = FindInLib(amedll->handle, "AMEOutputs");
   if (amedll->AMEOutputs  == NULL)
   {
      fprintf(stdout,"AMEOutputs not found.\n");
      return 0;
   }
   amedll->AMEWorkingDir = FindInLib(amedll->handle, "AMEWorkingDir");
   if (amedll->AMEWorkingDir  == NULL)
   {
      fprintf(stdout,"AMEWorkingDir not found.\n");
      return 0;
   }
   amedll->AMETerminate = FindInLib(amedll->handle, "AMETerminate");
   if (amedll->AMETerminate  == NULL)
   {
      fprintf(stdout,"AMETerminate not found.\n");
      return 0;
   }
   amedll->AMESetFinalTime = FindInLib(amedll->handle, "AMESetFinalTime");
   if (amedll->AMESetFinalTime  == NULL)
   {
      fprintf(stdout,"AMESetFinalTime not found.\n");
      return 0;
   }
   amedll->AMEInstallfprintf = FindInLib(amedll->handle, "AMEInstallfprintf");
   if (amedll->AMEInstallfprintf  == NULL)
   {
      fprintf(stdout,"AMEInstallfprintf not found.\n");
      return 0;
   }
   return 1;
}

/**
 * Unload dll loaded with loadamesimdll
 * Note that the pointer refered by amedll is not freed with this function
 * \sa loadamesimdll
 * \param amedll pointer to the AME_DLL structure to unload.
 * \return 1 on success, 0 on failure
 */
int unloadamesimdll(AME_DLL *amedll)
{
   /* Unload the DLL (or at least tell the operating system we no longer use it) */
#ifndef WIN32
#ifdef HPUX
   shl_unload(amedll->handle);
#else
   dlclose(amedll->handle);
#endif
#else
   FreeLibrary(amedll->handle);
#endif

   /* Then we clear the memory in the structure - to ensure that no-one calls any functions that is no longer available */

   memset(amedll, 0, sizeof(AME_DLL));
   return 1;
}

