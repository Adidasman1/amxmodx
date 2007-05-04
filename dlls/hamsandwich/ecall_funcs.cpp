#include "sdk/amxxmodule.h"

#include "offsets.h"
#include "ham_utils.h"
#include "hooklist.h"

#include "CVector.h"
#include "forward.h"
#include "hook.h"


extern CVector<Hook *> hooks[HAM_LAST_ENTRY_DONT_USE_ME_LOL];

void FailPlugin(AMX *amx, int id, int err, const char *reason);

inline void *GetFunction(void *pthis, int id)
{
	void **vtbl=GetVTable(pthis, Offsets.GetBase());

	int **ivtbl=(int **)vtbl;
	void *func=ivtbl[hooklist[id].vtid];

	return func;
}

#define SETUP(NUMARGS)					\
	if (((NUMARGS + 2) * sizeof(cell)) > (unsigned)params[0])	\
	{									\
		MF_LogError(amx, AMX_ERR_NATIVE, "Bad arg count.  Expected %d, got %d.", NUMARGS + 2, params[0] / sizeof(cell));	\
		return 0;						\
	}									\
	int func=params[1];					\
	int id=params[2];					\
	CHECK_FUNCTION(func);				\
	CHECK_ENTITY(id);					\
	void *pv=IndexToPrivate(id);


cell eCall_Void_Void(AMX *amx, cell *params)
{
	SETUP(0);

#ifdef _WIN32
	reinterpret_cast<void (__fastcall *)(void*, int)>(GetFunction(pv, func))(pv, 0);
#elif defined __linux__
	reinterpret_cast<void (*)(void *)>(GetFunction(pv, func))(pv);
#endif
	return 1;
}

cell eCall_Int_Void(AMX *amx, cell *params)
{
	SETUP(0);

#ifdef _WIN32
	return reinterpret_cast<int (__fastcall *)(void*, int)>(GetFunction(pv, func))(pv, 0);
#elif defined __linux__
	return reinterpret_cast<int (*)(void *)>(GetFunction(pv, func))(pv);
#endif
}

cell eCall_Void_Entvar(AMX *amx, cell *params)
{
	SETUP(1);

	int id3=*MF_GetAmxAddr(amx, params[3]);

	CHECK_ENTITY(id3);

	entvars_t *ev1=&(INDEXENT_NEW(id3)->v);

#ifdef _WIN32
	reinterpret_cast<void (__fastcall *)(void*, int, entvars_t *)>(GetFunction(pv, func))(pv, 0, ev1);
#elif defined __linux__
	reinterpret_cast<void (*)(void *, entvars_t *)>(GetFunction(pv, func))(pv, ev1);
#endif
	return 1;
}


cell eCall_Void_Cbase(AMX *amx, cell *params)
{
	SETUP(1);

	int id3=*MF_GetAmxAddr(amx, params[3]);

	CHECK_ENTITY(id3);

	void *pv1=(INDEXENT_NEW(id3)->pvPrivateData);

#ifdef _WIN32
	reinterpret_cast<void (__fastcall *)(void*, int, void *)>(GetFunction(pv, func))(pv, 0, pv1);
#elif defined __linux__
	reinterpret_cast<void (*)(void *, void *)>(GetFunction(pv, func))(pv, pv1);
#endif
	return 1;
}

cell eCall_Int_Float_Int(AMX *amx, cell *params)
{
	SETUP(2);

	float f3=amx_ftoc2(*MF_GetAmxAddr(amx, params[3]));
	int i4=*MF_GetAmxAddr(amx, params[4]);

#ifdef _WIN32
	return reinterpret_cast<int (__fastcall *)(void*, int, float, int)>(GetFunction(pv, func))(pv, 0, f3, i4);
#elif defined __linux__
	return reinterpret_cast<int (*)(void *, float, int)>(GetFunction(pv, func))(pv, f3, i4);
#endif
}

	
cell eCall_Void_Entvar_Int(AMX *amx, cell *params)
{
	SETUP(2);

	int id3=*MF_GetAmxAddr(amx, params[3]);
	int i4=*MF_GetAmxAddr(amx, params[4]);

	CHECK_ENTITY(id3);

	entvars_t *ev3=&(INDEXENT_NEW(id3)->v);

#ifdef _WIN32
	reinterpret_cast<void (__fastcall *)(void*, int, entvars_t *, int)>(GetFunction(pv, func))(pv, 0, ev3, i4);
#elif defined __linux__
	reinterpret_cast<void (*)(void *, entvars_t *, int)>(GetFunction(pv, func))(pv, ev3, i4);
#endif
	return 1;
}


cell eCall_Int_Cbase(AMX *amx, cell *params)
{
	SETUP(1);

	int id3=*MF_GetAmxAddr(amx, params[3]);

	CHECK_ENTITY(id3);

	void *pv1=(INDEXENT_NEW(id3)->pvPrivateData);

#ifdef _WIN32
	return reinterpret_cast<int (__fastcall *)(void*, int, void *)>(GetFunction(pv, func))(pv, 0, pv1);
#elif defined __linux__
	return reinterpret_cast<int (*)(void *, void *)>(GetFunction(pv, func))(pv, pv1);
#endif
}

cell eCall_Void_Int_Int(AMX *amx, cell *params)
{
	SETUP(2);

	int i3=*MF_GetAmxAddr(amx, params[3]);
	int i4=*MF_GetAmxAddr(amx, params[4]);

#ifdef _WIN32
	reinterpret_cast<void (__fastcall *)(void*, int, int, int)>(GetFunction(pv, func))(pv, 0, i3, i4);
#elif defined __linux__
	reinterpret_cast<void (*)(void *, int, int)>(GetFunction(pv, func))(pv, i3, i4);
#endif
	return 1;
}

cell eCall_Int_Int_Str_Int(AMX *amx, cell *params)
{
	
	SETUP(3);

	int i3=*MF_GetAmxAddr(amx, params[3]);
	char *sz4=MF_GetAmxString(amx, params[4], 0, NULL);
	int i5=*MF_GetAmxAddr(amx, params[5]);

#ifdef _WIN32
	return reinterpret_cast<int (__fastcall *)(void*, int, int, const char *, int)>(GetFunction(pv, func))(pv, 0, i3, sz4, i5);
#elif defined __linux__
	return reinterpret_cast<int (*)(void *, int, const char *, int)>(GetFunction(pv, func))(pv, i3, sz4, i5);
#endif
}

cell eCall_Int_Int(AMX *amx, cell *params)
{
	SETUP(1);

	int i3=*MF_GetAmxAddr(amx, params[3]);

#ifdef _WIN32
	return reinterpret_cast<int (__fastcall *)(void*, int, int)>(GetFunction(pv, func))(pv, 0, i3);
#elif defined __linux__
	return reinterpret_cast<int (*)(void *, int)>(GetFunction(pv, func))(pv, i3);
#endif
}

cell eCall_Int_Entvar(AMX *amx, cell *params)
{
	SETUP(1);

	int id3=*MF_GetAmxAddr(amx, params[3]);

	CHECK_ENTITY(id3);

	entvars_t *ev3=&(INDEXENT_NEW(id3)->v);

#ifdef _WIN32
	return reinterpret_cast<int (__fastcall *)(void *, int, entvars_t *)>(GetFunction(pv, func))(pv, 0, ev3);
#elif defined __linux__
	return reinterpret_cast<int (*)(void *, entvars_t *)>(GetFunction(pv, func))(pv, ev3);
#endif
}

cell eCall_Int_Entvar_Entvar_Float_Int(AMX *amx, cell *params)
{
	SETUP(4);

	int id3=*MF_GetAmxAddr(amx, params[3]);
	int id4=*MF_GetAmxAddr(amx, params[4]);
	float f5=amx_ctof2(*MF_GetAmxAddr(amx, params[5]));
	int i6=*MF_GetAmxAddr(amx, params[6]);

	CHECK_ENTITY(id3);
	CHECK_ENTITY(id4);

	entvars_t *ev3=&(INDEXENT_NEW(id3)->v);
	entvars_t *ev4=&(INDEXENT_NEW(id4)->v);

#ifdef _WIN32
	return reinterpret_cast<int (__fastcall *)(void *, int, entvars_t *, entvars_t *, float, int)>(GetFunction(pv, func))(pv, 0, ev3, ev4, f5, i6);
#elif defined __linux__
	return reinterpret_cast<int (*)(void *, entvars_t *, entvars_t *, float, int)>(GetFunction(pv, func))(pv, ev3, ev4, f5, i6);
#endif
}

cell eCall_Void_Int(AMX *amx, cell *params)
{
	SETUP(1);

	int i3=*MF_GetAmxAddr(amx, params[3]);

#ifdef _WIN32
	reinterpret_cast<void (__fastcall *)(void *, int, int)>(GetFunction(pv, func))(pv, 0, i3);
#elif defined __linux__
	reinterpret_cast<void (*)(void *, int)>(GetFunction(pv, func))(pv, i3);
#endif

	return 1;
}

cell eCall_Void_Cbase_Cbase_Int_Float(AMX *amx, cell *params)
{
	SETUP(4);

	int id3=*MF_GetAmxAddr(amx, params[3]);
	int id4=*MF_GetAmxAddr(amx, params[4]);
	int i5=*MF_GetAmxAddr(amx, params[5]);
	float f6=amx_ctof(*MF_GetAmxAddr(amx, params[6]));

	CHECK_ENTITY(id3);
	CHECK_ENTITY(id4);

	void *p3=IndexToPrivate(id3);
	void *p4=IndexToPrivate(id4);

#ifdef _WIN32
	reinterpret_cast<void (__fastcall *)(void *, int, void *, void *, int, float)>(GetFunction(pv, func))(pv, 0, p3, p4, i5, f6);
#elif defined __linux__
	reinterpret_cast<void (*)(void *, void *, void *, int, float)>(GetFunction(pv, func))(pv, p3, p4, i5, f6);
#endif

	return 1;
}

cell eCall_Void_Entvar_Float_Vector_Trace_Int(AMX *amx, cell *params)
{
	SETUP(5);

	int id3=*MF_GetAmxAddr(amx, params[3]);
	float f4=amx_ctof2(*MF_GetAmxAddr(amx, params[4]));
	Vector v5;
	TraceResult *tr6=reinterpret_cast<TraceResult *>(*MF_GetAmxAddr(amx, params[6]));
	int i7=*MF_GetAmxAddr(amx, params[7]);

	float *fl5=(float *)MF_GetAmxAddr(amx, params[5]);
	v5.x=fl5[0];
	v5.y=fl5[1];
	v5.z=fl5[2];

	if (tr6==NULL)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Null traceresult provided.");

		return 0;
	}

	CHECK_ENTITY(id3);

	entvars_t *ev3=&(INDEXENT_NEW(id3)->v);
#ifdef _WIN32
	reinterpret_cast<void (__fastcall *)(void *, int, entvars_t *, float, Vector, TraceResult *, int)>(GetFunction(pv, func))(pv, 0, ev3, f4, v5, tr6, i7);
#elif defined __linux__
	reinterpret_cast<void (*)(void *, entvars_t *, float, Vector, TraceResult *, int)>(GetFunction(pv, func))(pv, ev3, f4, v5, tr6, i7);
#endif

	return 1;
}

cell eCall_Void_Float_Vector_TraceResult_Int(AMX *amx, cell *params)
{
	SETUP(4);

	float f3=amx_ctof2(*MF_GetAmxAddr(amx, params[3]));
	Vector v4;
	TraceResult *tr5=reinterpret_cast<TraceResult *>(*MF_GetAmxAddr(amx, params[5]));
	int i6=*MF_GetAmxAddr(amx, params[6]);

	float *fl4=(float *)MF_GetAmxAddr(amx, params[4]);
	v4.x=fl4[0];
	v4.y=fl4[1];
	v4.z=fl4[2];

	if (tr5==NULL)
	{
		MF_LogError(amx, AMX_ERR_NATIVE, "Null traceresult provided.");

		return 0;
	}

#ifdef _WIN32
	reinterpret_cast<void (__fastcall *)(void *, int, float, Vector, TraceResult *, int)>(GetFunction(pv, func))(pv, 0, f3, v4, tr5, i6);
#elif defined __linux__
	reinterpret_cast<void (*)(void *, float, Vector, TraceResult *, int)>(GetFunction(pv, func))(pv, f3, v4, tr5, i6);
#endif

	return 1;
}

cell eCall_Str_Void(AMX *amx, cell *params)
{
	SETUP(2);

#ifdef _WIN32
	char *v=reinterpret_cast<char *(__fastcall *)(void *, int)>(GetFunction(pv, func))(pv, 0);
#elif defined __linux__
	char *v=reinterpret_cast<char *(*)(void *)>(GetFunction(pv, func))(pv);
#endif
	return MF_SetAmxString(amx, params[3], v == NULL ? "" : v, *MF_GetAmxAddr(amx, params[4]));

}

cell eCall_Cbase_Void(AMX *amx, cell *params)
{
	SETUP(0);
#ifdef _WIN32
	void *ret=reinterpret_cast<void *(__fastcall *)(void *, int)>(GetFunction(pv, func))(pv, 0);
#elif defined __linux__
	void *ret=reinterpret_cast<void *(*)(void *)>(GetFunction(pv, func))(pv);
#endif
	return PrivateToIndex(ret);
}

cell eCall_Vector_Void(AMX *amx, cell *params)
{
	SETUP(1);
#ifdef _WIN32
	Vector ret=reinterpret_cast<Vector (__fastcall *)(void *, int)>(GetFunction(pv, func))(pv, 0);
#elif defined __linux__
	Vector ret=reinterpret_cast<Vector (*)(void *)>(GetFunction(pv, func))(pv);
#endif
	float *out=(float *)MF_GetAmxAddr(amx, params[3]);
	out[0]=ret.x;
	out[1]=ret.y;
	out[2]=ret.z;

	return 1;
}

cell eCall_Vector_pVector(AMX *amx, cell *params)
{
	SETUP(2);

	Vector v3;
	float *fl3=(float *)MF_GetAmxAddr(amx, params[3]);
	v3.x=fl3[0];
	v3.y=fl3[1];
	v3.z=fl3[2];

#ifdef _WIN32
	Vector ret=reinterpret_cast<Vector (__fastcall *)(void *, int, Vector*)>(GetFunction(pv, func))(pv, 0, &v3);
#elif defined __linux__
	Vector ret=reinterpret_cast<Vector (*)(void *, Vector*)>(GetFunction(pv, func))(pv, &v3);
#endif
	float *out=(float *)MF_GetAmxAddr(amx, params[4]);
	out[0]=ret.x;
	out[1]=ret.y;
	out[2]=ret.z;

	fl3[0]=v3.x;
	fl3[1]=v3.y;
	fl3[2]=v3.z;

	return 1;
}

cell eCall_Int_pVector(AMX *amx, cell *params)
{
	SETUP(1);

	Vector v3;
	float *fl3=(float *)MF_GetAmxAddr(amx, params[3]);
	v3.x=fl3[0];
	v3.y=fl3[1];
	v3.z=fl3[2];

#ifdef _WIN32
	int ret=reinterpret_cast<int (__fastcall *)(void *, int, Vector*)>(GetFunction(pv, func))(pv, 0, &v3);
#elif defined __linux__
	int ret=reinterpret_cast<int (*)(void *, Vector*)>(GetFunction(pv, func))(pv, &v3);
#endif

	fl3[0]=v3.x;
	fl3[1]=v3.y;
	fl3[2]=v3.z;

	return ret;
}

cell eCall_Void_Entvar_Float_Float(AMX *amx, cell *params)
{
	SETUP(3);

	int id3=*MF_GetAmxAddr(amx, params[3]);
	float f4=amx_ctof2(*MF_GetAmxAddr(amx, params[4]));
	float f5=amx_ctof2(*MF_GetAmxAddr(amx, params[5]));

	CHECK_ENTITY(id3);

	entvars_t *ev3=&(INDEXENT_NEW(id3)->v);

#ifdef _WIN32
	reinterpret_cast<void (__fastcall *)(void *, int, entvars_t *, float, float)>(GetFunction(pv, func))(pv, 0, ev3, f4, f5);
#elif defined __linux__
	reinterpret_cast<void (*)(void *, entvars_t *, float, float)>(GetFunction(pv, func))(pv, ev3, f4, f5);
#endif

	return 1;
}

cell eCall_Int_pFloat_pFloat(AMX *amx, cell *params)
{
	SETUP(2);

	float f3=amx_ctof2(*MF_GetAmxAddr(amx, params[3]));
	float f4=amx_ctof2(*MF_GetAmxAddr(amx, params[4]));

#ifdef _WIN32
	return reinterpret_cast<int (__fastcall *)(void *, int, float*, float*)>(GetFunction(pv, func))(pv, 0, &f3, &f4);
#elif defined __linux__
	return reinterpret_cast<int (*)(void *, float*, float*)>(GetFunction(pv, func))(pv, &f3, &f4);
#endif

}

cell eCall_Void_Entvar_Float(AMX *amx, cell *params)
{
	SETUP(2);

	int id3=*MF_GetAmxAddr(amx, params[3]);
	float f4=amx_ctof2(*MF_GetAmxAddr(amx, params[4]));

	CHECK_ENTITY(id3);

	entvars_t *ev3=&(INDEXENT_NEW(id3)->v);

#ifdef _WIN32
	return reinterpret_cast<int (__fastcall *)(void *, int, entvars_t*, float)>(GetFunction(pv, func))(pv, 0, ev3, f4);
#elif defined __linux__
	return reinterpret_cast<int (*)(void *, entvars_t*, float)>(GetFunction(pv, func))(pv, ev3, f4);
#endif
}
