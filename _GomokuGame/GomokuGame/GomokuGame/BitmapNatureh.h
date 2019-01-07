#ifndef _GETBITMAPNATUREH_H_
#define _GETBITMAPNATUREH_H_
#pragma pack(2)
//#include"stdafx.h"
#ifdef __cplusplus
extern "C" {
#endif
	///*����WORDΪ�����ֽڵ�����*/
	//typedef unsigned short WORD;
	///*����DWORDΪe�ĸ��ֽڵ�����*/
	//typedef unsigned long DWORD;

	/*λͼ�ļ�ͷ*/
	typedef struct BMP_FILE_HEADER{
		WORD bType; /* �ļ���ʶ�� */
		DWORD bSize; /* �ļ��Ĵ�С */
		WORD bReserved1; /* ����ֵ,��������Ϊ0 */
		WORD bReserved2; /* ����ֵ,��������Ϊ0 */
		DWORD bOffset; /* �ļ�ͷ�����ͼ������λ��ʼ��ƫ���� */
	} BMPFILEHEADER;

	/*λͼ��Ϣͷ*/
	typedef struct BMP_INFO{
		DWORD bInfoSize; /* ��Ϣͷ�Ĵ�С */
		DWORD bWidth; /* ͼ��Ŀ�� */
		DWORD bHeight; /* ͼ��ĸ߶� */
		WORD bPlanes; /* ͼ���λ���� */
		WORD bBitCount; /* ÿ�����ص�λ�� */
		DWORD bCompression; /* ѹ������ */
		DWORD bmpImageSize; /* ͼ��Ĵ�С,���ֽ�Ϊ��λ */
		DWORD bXPelsPerMeter; /* ˮƽ�ֱ��� */
		DWORD bYPelsPerMeter; /* ��ֱ�ֱ��� */
		DWORD bClrUsed; /* ʹ�õ�ɫ���� */
		DWORD bClrImportant; /* ��Ҫ����ɫ�� */
	} BMPINF;

	/*��ɫ��*/
	typedef struct RGB_QUAD {
		WORD rgbBlue; /* ��ɫǿ�� */
		WORD rgbGreen; /* ��ɫǿ�� */
		WORD rgbRed; /* ��ɫǿ�� */
		WORD rgbReversed; /* ����ֵ */
	} RGBQUAD_MY;
	int __stdcall GetBitmapNature(const char *BmpName, BMPINF *lpBmpInf, int iBmpInfSize);
	int __stdcall GetBitmapRGB(const char *BmpName, RGBQUAD_MY *lpRgbQuad, int lpRgbQuadSize);
#ifdef __cplusplus
}
#endif
#endif