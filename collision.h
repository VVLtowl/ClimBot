#pragma once


//*****************************************************************************
// マクロ定義
//*****************************************************************************
bool CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionBC(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float size1, float size2);
int CollisionBCDir4(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
int CollisionBBDir4_2(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
bool CollisionCsC(D3DXVECTOR2 circlePos, D3DXVECTOR2 rectCirclePos, D3DXVECTOR2 rectCircleVec, float circleR, float rectCircleR);
//*****************************************************************************
// 構造体定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void UpdateCollision(void);

