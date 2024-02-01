#pragma once
#include "imaterial.hpp"

#define MAX_AREA_STATE_BYTES 32
#define MAX_AREA_PORTAL_STATE_BYTES 24

struct VisibleFogVolumeInfo_t;
class IWorldRenderList;
struct VisOverrideData_t;
class IBrushRenderer;
class Frustum;
struct DrawBrushModelMode_t;
class WorldListInfo_t;

enum ERenderDepthMode
{
	DEPTH_MODE_NORMAL = 0,
	DEPTH_MODE_SHADOW = 1,
	DEPTH_MODE_SSA0 = 2,
	DEPTH_MODE_OVERRIDE = 3,
	DEPTH_MODE_MAX
};

class IVRenderView
{
public:
	virtual void DrawBrushModel(void* baseentity, void* model, const vec3_t& origin, const vec3_t& angles, bool bUnused) = 0;
	virtual void DrawIdentityBrushModel(IWorldRenderList* pList, void* model) = 0;
	virtual void TouchLight(struct dlight_t* light) = 0;
	virtual void Draw3DDebugOverlays(void) = 0;
	virtual void SetBlend(float blend) = 0;
	virtual float GetBlend(void) = 0;
	virtual void SetColorModulation(float const* blend) = 0;
	inline void SetColorModulation(float r, float g, float b) {
		float clr[3] = { r, g, b };
		SetColorModulation(clr);
	}

	inline void SetColorModulation( clr_t col ) {
		float clr[3] = { ( float )col.r( ) / 255.f, ( float )col.g( ) / 255.f, ( float )col.b( ) / 255.f };
		SetColorModulation(clr);
	}
	virtual void GetColorModulation(float* blend) = 0;
	virtual void SceneBegin(void) = 0;
	virtual void SceneEnd(void) = 0;
	virtual void GetVisibleFogVolume(const vec3_t& eyePoint, VisibleFogVolumeInfo_t* pInfo) = 0;
	virtual IWorldRenderList* CreateWorldList() = 0;
	virtual void BuildWorldLists(IWorldRenderList* pList, WorldListInfo_t* pInfo, int iForceFViewLeaf, const VisOverrideData_t* pVisData = NULL, bool bShadowDepth = false, float* pReflectionWaterHeight = NULL) = 0;
	virtual void DrawWorldLists(IWorldRenderList* pList, unsigned long flags, float waterZAdjust) = 0;
	virtual void DrawTopView(bool enable) = 0;
	virtual void TopViewBounds(vec2_t const& mins, vec2_t const& maxs) = 0;
	virtual void DrawLights(void) = 0;
	virtual void DrawMaskEntities(void) = 0;
	virtual void DrawTranslucentSurfaces(IWorldRenderList* pList, int sortIndex, unsigned long flags, bool bShadowDepth) = 0;
	virtual void DrawLineFile(void) = 0;
	virtual void DrawLightmaps(IWorldRenderList* pList, int pageId) = 0;
	virtual void ViewSetupVis(bool novis, int numorigins, const vec3_t origin[]) = 0;
	virtual bool AreAnyLeavesVisible(int* leafList, int nLeaves) = 0;
	virtual	void VguiPaint(void) = 0;
	virtual void ViewDrawFade(std::byte* color, IMaterial* pMaterial) = 0;
	virtual void OLD_SetProjectionMatrix(float fov, float zNear, float zFar) = 0;
	virtual clr_t GetLightAtPoint(vec3_t& pos) = 0;
	virtual int GetViewEntity(void) = 0;
	virtual float GetFieldOfView(void) = 0;
	virtual unsigned char** GetAreaBits(void) = 0;
	virtual void SetFogVolumeState(int nVisibleFogVolume, bool bUseHeightFog) = 0;
	virtual void InstallBrushSurfaceRenderer(IBrushRenderer* pBrushRenderer) = 0;
	virtual void DrawBrushModelShadow(void* pRenderable) = 0;
	virtual	bool LeafContainsTranslucentSurfaces(IWorldRenderList* pList, int sortIndex, unsigned long flags) = 0;
	virtual bool DoesBoxIntersectWaterVolume(const vec3_t& mins, const vec3_t& maxs, int leafWaterDataID) = 0;
	virtual void SetAreaState(unsigned char chAreaBits[MAX_AREA_STATE_BYTES], unsigned char chAreaPortalBits[MAX_AREA_PORTAL_STATE_BYTES]) = 0;
	virtual void VGui_Paint(int mode) = 0;
	virtual void Push3DView(const CViewSetup& view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes) = 0;
	virtual void Push2DView(const CViewSetup& view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes) = 0;
	virtual void PopView(Frustum frustumPlanes) = 0;
	virtual void SetMainView(const vec3_t& vecOrigin, const vec3_t& angles) = 0;
	virtual void ViewSetupVisEx(bool novis, int numorigins, const vec3_t origin[], unsigned int& returnFlags) = 0;
	virtual void OverrideViewFrustum(Frustum custom) = 0;
	virtual void DrawBrushModelShadowDepth(void* baseentity, void* model, const vec3_t& origin, const vec3_t& angles, ERenderDepthMode DepthMode) = 0;
	virtual void UpdateBrushModelLightmap(void* model, void* pRenderable) = 0;
	virtual void BeginUpdateLightmaps(void) = 0;
	virtual void EndUpdateLightmaps(void) = 0;
	virtual void OLD_SetOffCenterProjectionMatrix(float fov, float zNear, float zFar, float flAspectRatio, float flBottom, float flTop, float flLeft, float flRight) = 0;
	virtual void OLD_SetProjectionMatrixOrtho(float left, float top, float right, float bottom, float zNear, float zFar) = 0;
	virtual void Push3DView(const CViewSetup& view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes, ITexture* pDepthTexture) = 0;
	virtual void GetMatricesForView(const CViewSetup& view, vmatrix_t* pWorldToView, vmatrix_t* pViewToProjection, vmatrix_t* pWorldToProjection, vmatrix_t* pWorldToPixels) = 0;
	virtual void DrawBrushModelEx(void* baseentity, void* model, const vec3_t& origin, const vec3_t& angles, DrawBrushModelMode_t mode) = 0;
};