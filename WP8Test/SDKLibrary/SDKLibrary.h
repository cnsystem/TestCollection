// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� SDKLIBRARY_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// SDKLIBRARY_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef SDKLIBRARY_EXPORTS
#define SDKLIBRARY_API __declspec(dllexport)
#else
#define SDKLIBRARY_API __declspec(dllimport)
#endif

// �����Ǵ� SDKLibrary.dll ������
class SDKLIBRARY_API CSDKLibrary {
public:
	CSDKLibrary(void);
	// TODO: �ڴ�������ķ�����
};

extern SDKLIBRARY_API int nSDKLibrary;

SDKLIBRARY_API int fnSDKLibrary(void);
