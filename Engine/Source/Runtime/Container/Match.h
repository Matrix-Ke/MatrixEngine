#pragma once
#include "Container.h"
#include "Array.h"

#include "Core/File.h"
#include "Math/Math.h"


namespace Matrix::Container
{
	/*
	��ģʽƥ����ƥ��['name'][s>0][s=5][s<10][f][i]�����Կո�ֿ����ַ��� ������������
	�㷨ʵ��:���ڡ�3D��Ϸ��̴�ʦ���ɡ�����ʵ���㷨û�и���������ʵ���߼����ӣ��������
	���������Զ���������ʵ��(��ʵ���к�ƥ���йص�����������Զ����Ͳ���ʽ���������ɽ��)
	�����㷨�������ˣ�������������Զ����Լ����Ժ����ɵ�д��������ģ�
	���ģʽƥ��������̶�ģʽƥ�䲻ͬ��ģʽ�����ǹ̶��ģ�������Ҫ��ģʽ����Ϊ�Զ�����
	������,�������Է�Ϊ4�����̣�['name']���̶ֹ���ƥ��,[s>0]���ֲ�����ƥ��,[f]����ƥ��
	[i]����ƥ��,����ģʽ��ƥ���(Ҳ����ģʽ��ƥ���),���ж�ƥ�䴮�Ƿ����Ҫ��
	*/
	class MATRIX_CONTAINER_API MMatch
	{
	private:
		void Clear();
		//ģʽƥ���Զ�������
		//��ʼ״̬
		bool Begin();
		// ״̬1 
		bool Fun1();
		//״̬ 2 
		bool Fun2();
		// �̶��ַ���ƥ��״̬
		bool FunStrMatch();
		// �����ַ���ƥ��ƥ�� 
		bool FunStr_I_Match();
		// ��ģʽ���ַ������ж�ƥ��
		int FunIntMatch_D();

		// ��ƥ�䴮����ƥ��
		bool FunIntMatch();
		// ��ƥ�䴮���㴮ƥ��
		bool FunFloMatch();
		Core::File File;
	public:
		enum { BUFFER_SIZE = 100, MAX_ARGS = 16, MAX_COMMENT = 80 };
		MMatch();
		~MMatch();
		bool Open(TCHAR* filename);
		bool Getline();
		//ƥ�亯��
		bool PatternMatch(TCHAR* _pattern);
		TCHAR buffer[BUFFER_SIZE];			//�л���
		TCHAR* pattern;
		int  b_index;
		int	 p_index;
		int  length;						//��ǰ�г���
		int  num_lines;						//��������
		//ģʽ����ֵ
		TCHAR  pstrings[MAX_ARGS][BUFFER_SIZE]; // any strings
		int   num_pstrings;
		MArray<VSREAL> pfloats;               // any floats
		MArray<int>pints;						// any ints

	}; // end CLASS CPARS
}
