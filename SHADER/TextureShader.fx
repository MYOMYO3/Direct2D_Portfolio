////////// VTX
struct VTX_IN
{
    float4 vPos : POSITION;
    float2 vUv : TEXCOORD; // �ؽ�ó ��ǥ
    float4 vCol : COLOR; // ����
};

struct VTX_OUT
{
    float4 vPos : SV_POSITION;
    float2 vUv : TEXCOORD; // �ؽ�ó ��ǥ
    float4 vCol : COLOR; // ����
};

struct TEST
{
    float4 vColor;
};

// ���
cbuffer MATDATA : register(b0)
{
    matrix WVP;
}

// �ؽ�ó�� �Ϻκи� ������ �ϱ� ���� FLOAT4�� �ʿ�.
cbuffer CUTDATA : register(b1)
{
    float4 CutUv;
    // x y�� �������� ����.
    // z w���� ũ�⸦ �־��� ���̴�.
    // ��������?
    // 0.25 0.25 ������
    // 0.5 0.5 ũ��
}

cbuffer COLDATA : register(b2)
{
    float4 COL;
}

cbuffer HPDATA : register(b3)
{
    float HP;
}

VTX_OUT VS_TEX(VTX_IN _in)
{
    // �Ϻκи� ������ �Ѵٴ� �̾߱��
    // 

    // 0 0 | 1 0
    // 0 1 | 1 1

    //   0.25 0.25   | 0.75    0.25 
    //   0.25 0.75F   | 0.75  0.75

    VTX_OUT Out = (VTX_OUT) 0.0f;
    Out.vCol = _in.vCol;
    

    //           1           0.5        0.25
    Out.vUv.x = (_in.vUv.x * CutUv.z) + CutUv.x;
    //           0           0.5        0.25
    Out.vUv.y = (_in.vUv.y * CutUv.w) + CutUv.y;

    // Out.vUv = _in.vUv;

    Out.vPos = mul(_in.vPos, WVP);





    return Out;
}


///// PIX



struct PIX_OUT
{
    float4 vOutColor : SV_Target;
};

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

PIX_OUT PS_TEX(VTX_OUT _in)
{
    PIX_OUT Out = (PIX_OUT) 0.0f;
    Out.vOutColor = Tex.Sample(Smp, _in.vUv); // �̺κ�
    
    
    Out.vOutColor.a *= COL.a; //0.55f;

    if (0.0f == Out.vOutColor.a)
    {
        clip(-1); //���ȼ��� �����ض�
    }

    // 0.9�� ������ 0.9~ 1.0���� Ŭ��
    //if (Uv.x > 0.7f)
    if (_in.vUv.x > HP.x)
    {
        clip(-1);
    }

    //_in.vUv.x = HP;

    
    
    //if (HP)
    //{
    //    clip(-1);
    //}



    //TEST colorTest = {0.0f, 0.0f, 0.0f, 1.0f };
    //Out.vOutColor.r = COL.r;     
    
    
    //float4 black = { 0.0f, 0.0f, 0.0f, 1.0f};
    //if (0.0f == Out.vOutColor.r && 0.0f == Out.vOutColor.g && 0.0f == Out.vOutColor.b)
    //{
    //    clip(-1); //���ȼ��� �����ض�
    //}

    
    //if (0.0f == Out.vOutColor.rgb )
    //{
    //    clip(-1); //���ȼ��� �����ض�
    //}

    //int r = Out.vOutColor.r * 256;
    //int g = Out.vOutColor.r * 256;
    //int b = Out.vOutColor.r * 256;

    ////Out.vOutColor.x *= 10.0f;
    ////Out.vOutColor.y *= 10.0f;
    ////Out.vOutColor.z *= 10.0f;
    
    //if(15 < r && 17 > r )
    //{
    //    Out.vOutColor.x *= 20.0f;
    //    Out.vOutColor.y *= 20.0f;
    //    Out.vOutColor.z *= 20.0f;
    //    Out.vOutColor.a = 0.5f;
    //}
    



    return Out;
}