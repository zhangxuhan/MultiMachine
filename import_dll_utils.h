#ifndef __IMPORT_DLL_UTILS__
#define __IMPORT_DLL_UTILS__

typedef struct AME_DLL  *AME_DLL_PTR;

typedef struct AME_DLL
{
	/** Initializes AMESim model
		\sa AMETerminate
	*/
	void(*AMEInitModel)(
		double time,           /**< initial time value */
		double printInterval,  /**< output interval for the AMESim result file */
		double maxTimeStep,    /**< max timestep to be used in the model */
		double tolerance,      /**< tolerance value */
		int errCtrl,           /**< type of error check, mixed=0, relative= or absolute */
		int writeLevel,        /**< write level 0 for time, 1 for full and 2 for no output */
		int extraDisconPrints, /**< extra discon prints if 1 */
		int runStats,          /**< runstats if 1 */
		int runType,           /**< run type, 8 for normal run */
		int thesolvertype,     /**< currently unused (set to zero) */
		int numInputs,         /**< num inputs to the AMESim model */
		int numOutputs,        /**< num outputs from the AMESim model */
		double *theInputs,     /**< vector with inputs to the AMESim model */
		double *theOutputs     /**< vector with outputs from the AMESim model */
		);
	/** integrate models until t, then retrieve model outputs and set input values
		Similar to:
		\code
		AMEOutputs(t, numOutputs, theOutputs);
		AMEInputs(numInputs, theInputs);
		\endcode
		\sa AMEdoAStep2
		\return 1 on success, 0 on failure
	*/
	int(*AMEdoAStep)(
		double t,               /**< final integration time */
		int numInputs,          /**< num inputs to the AMESim model */
		int numOutputs,         /**< num outputs from the AMESim model */
		const double *theInputs,/**< vector with inputs to the AMESim model */
		double *theOutputs      /**< vector with outputs from the AMESim model */
		);
	/** Set model input values, then integrate until t and send back model outputs
		Similar to:
		\code
		AMEInputs(numInputs, theInputs);
		AMEOutputs(t, numOutputs, theOutputs);
		\endcode
		\sa AMEdoAStep
		\return 1 on success, 0 on failure
	*/
	int(*AMEdoAStep2)(
		double t,               /**< final integration time */
		int numInputs,          /**< num inputs to the AMESim model */
		int numOutputs,         /**< num outputs from the AMESim model */
		const double *theInputs,/**< vector with inputs to the AMESim model */
		double *theOutputs      /**< vector with outputs from the AMESim model */
		);
	/** Set model input values for the current date
		\sa AMEOutputs
		\return 1 on success, 0 on failure
	*/
	int(*AMEInputs)(
		int numInputs,          /**< num inputs to the AMESim model */
		const double *theInputs /**< vector with inputs to the AMESim model */
		);
	/** Integrate until date t and then retrieve output values from the model
		\sa AMEInputs
		\return 1 on success, 0 on failure
	*/
	int(*AMEOutputs)(
		double t,               /**< final integration time */
		int numOutputs,         /**< num outputs from the AMESim model */
		double *theOutputs      /**< vector with outputs from the AMESim model */
		);
	/** Get sizes from the model
		\return 1 on success, 0 on failure
	*/
	int(*AMEInitSizes)(
		int *numinputs,         /**< number of inputs to the AMESim model */
		int *numoutput,         /**< number of outputs from the AMESim model */
		int *numstates,         /**< number of state variables in AMESim model */
		int *numimplicit        /**< number of implicit variables in AMESim model */
		);
	/** tells the model that the simulation is done. This call is mandatory before the next AMEInitModel */
	void(*AMETerminate)(void);
	/** By default, the shared library built with AMESim searches for configuration, data and parameter files in the current working directory. To call the shared library from another directory, use AMEWorkingDir to configure the path to the directory that contains configuration, data and parameter files
	\sa AMEInitModel
	\return 1 on success, 0 on failure
	*/
	int(*AMEWorkingDir)(
		char *dir  /**< path to the directory that contains AMESim model files */
		);
	/** set AMESim model maximum integration time
		\return 1 on success, 0 on failure
	*/
	int(*AMESetFinalTime)(
		double time             /**< max integration time */
		);
	/** AMESim models usually write status or error message to stdout, stderr.
		You can use your own function to print these messages. For instance, redirect message to a file:
	   \code
	   // define your own log function
	   static FILE *logpf;
	   static int amelogfprintf(FILE *fp, const char *fmt, va_list ap)
	   {
		  int ans = 0;
		  // redirect stdout and stderr toward the filedescriptor
		  if( logpf != NULL && ((fp == stdout) || (fp == stderr)) )
		  {
			 ans=vfprintf(logpf, fmt, ap);
			 fflush(logpf);
		  }
		  // don't redirect write in files
		  else
		  {
			 ans=vfprintf(fp, fmt, ap);
		  }
		  return ans;
	   }
	   // ...
	   // use your own log function
	   logpf = fopen("mylogfile", "a");
	   AMEInstallfprintf(amelogfprintf);
	   \endcode
	   \param newameInternalfprintf pointer to the new printf function. See documentation of vfprintf for more info
	   \return 1 on success, 0 on failure
	*/
	int(*AMEInstallfprintf)(
		int(*newameInternalfprintf)(void *)
		);

	int(*AMESetUpFixedStepSolver)(
		double start_time,
		int numinputs,
		int numoutputs,
		int solvertype, /* ab or rk*/
		int RK_order,
		double fixedstepsize,
		double printInterval
		);

	/** internal pointer */
	void *handle;

	int(*AMESetUpFixedStepSolver2)(
		double start_time,
		int numinputs,
		int numoutputs,
		int run_type,
		int solver_type,
		int RK_order,
		double fixedstepsize,
		double printInterval
		);

	int(*AMEInitModelFailSafe)(double time,           /**< initial time value */
		double PrintInterval,  /**< output interval for the AMESim result file */
		double MaxTimeStep,    /**< max timestep to be used in the model */
		double tolerance,      /**< tolerance value */
		int errCtrl,           /**< type of error check, mixed=0, relative= or absolute */
		int writeLevel,        /**< write level 0 for time, 1 for full and 2 for no output */
		int extraDisconPrints, /**< extra discon prints if 1 */
		int runStats,          /**< runstats if 1 */
		int runType,           /**< run type, 8 for normal run */
		int thesolvertype,     /**< currently unused (set to zero) */
		int numInputs,         /**< num inputs to the AMESim model */
		int numOutputs,        /**< num outputs from the AMESim model */
		double *theInputs,     /**< vector with inputs to the AMESim model */
		double *theOutputs);   /**< vector with outputs from the AMESim model */

	int(*AMEdoAStep2FailSafe)(double t, int numInputs, int numOutputs, const double *theInputs,
		double *theOutputs);

	int(*AMEdoAStepFailSafe)(double t, int numInputs, int numOutputs, const double *theInputs,
		double *theOutputs);

	int(*AMESetUpFixedStepSolverFailSafe2)(double start_time, int numinputs, int numoutputs,
		int run_type,          /* */
		int solver_type,       /* 2 for RK 1 for Adams-Bashforth (1 for Euler - with order 1)*/
		int solver_order,      /* order of solver */
		double fixed_h,        /* step used in solver*/
		double printinterval); /* save interval for result file - negative if no resultfile */

	int(*AMEChangeOrAddRealGlobalParamValue)(const char* param, double value);
	int(*AMEChangeOrAddIntGlobalParamValue)(const char* param, int value);
	int(*AMEChangeOrAddTextGlobalParamValue)(const char* param, const char* value);

	int(*AMEModelGetInputVariables)(int *numinputs, char ***inputlabels, char ***units);
	int(*AMEModelGetOutputVariables)(int *numoutputs, char ***outputlabels, char ***units);
	void(*AMEModelFreeVariableLablesAndUnits)(int *numvars, char ***labels, char ***units);

	/* The following initfixedstep, initvarstep, dostep2 and dostep are redirections from the
	   entrypoints in the DLL. They will return 0 for OK and non-zero for failure.
	   The will use "failsafe" methods if they are available in the DLL. */

	int(*initfixedstep)(AME_DLL_PTR amedll,
		double start_time,
		int numinputs,
		int numoutputs,
		int run_type,
		int solver_type,
		int RK_order,
		double fixedstepsize,
		double printInterval);

	int(*initvarstep)(AME_DLL_PTR amedll,
		double time,
		double PrintInterval,
		double MaxTimeStep,
		double tolerance,
		int errCtrl,           /**< type of error check, mixed=0, relative= or absolute */
		int writeLevel,        /**< write level 0 for time, 1 for full and 2 for no output */
		int extraDisconPrints, /**< extra discon prints if 1 */
		int runStats,          /**< runstats if 1 */
		int runType,           /**< run type, 8 for normal run */
		int thesolvertype,     /**< currently unused (set to zero) */
		int numInputs,         /**< num inputs to the AMESim model */
		int numOutputs,        /**< num outputs from the AMESim model */
		double *theInputs,     /**< vector with inputs to the AMESim model */
		double *theOutputs);   /**< vector with outputs from the AMESim model */

	int(*dostep2)(AME_DLL_PTR amedll,
		double time,
		int numInputs,
		int numOutputs,
		double *theInputs,
		double *theOutputs);

	int(*dostep)(AME_DLL_PTR amedll,
		double time,
		int numInputs,
		int numOutputs,
		double *theInputs,
		double *theOutputs);

	/* add additional functions at the end of the struct - to maintain some upwards binary compatibility */
	int(*AMEdoExtrapolatedStep)(double t, const unsigned int *oki, const double **pki, double *theOutputs);

} AME_DLL;

#ifdef __cplusplus
extern "C" {
#endif

	int loadamesimdll(char *libname, AME_DLL *amedll);
	int unloadamesimdll(AME_DLL *theamedll);

#ifdef __cplusplus
}
#endif

#endif
