/**
Math:
@description: This section includes math methods created for Final Engine, 
	i.e., the one to produce random numbers.
@created: 2013.8.28
@author: ������
@reference:
	1. ��Ϸ������Ƹ���, P97-102, 
*/

#include "stdafx.h"
#include <time.h>
namespace FinalEngine
{

	/** 
	����������ࣨԤ�Ƚ����������ʽ��:
	�����ܲ���һ��ֵ��Χ�ڵ����������������ƽ���ֲ���
	������һ��ֵ�������������ʱ��������ȷ����1�Σ�����
	ֵ���������Զ�����Ϊfalseʱ��Ҫ�����������
	*/
	class RandomNum
	{
	public:
		RandomNum(unsigned int Range, bool AutoGen = false)
			: mRange(Range), mTable(NULL), mIndex(0), mAutoGenerate(AutoGen)
		{
			srand((unsigned)time(NULL)); // ʹ��ʱ������������
			mRange = Range;
			mTable = new int [mRange];
			Generate(); // ���������
		}
		virtual ~RandomNum()
		{
			if (mTable != NULL)
			{
				delete [] mTable;
				mTable = NULL;
			}
			mRange = 0;
		}

		// ȡ�������
		int GetNumber(void)
		{
			int number = -1;
			if (mRange > 0)
			{
				number = mTable[mIndex]; // ȡ�������
				++mIndex;
				if (mIndex >= mRange)
				{
					mIndex = 0;
					if (mAutoGenerate) // ���²��������
					{
						Generate();
					}
				}
			}
			return number;
		}

		// ���������
		void Generate(void)
		{
			int loop, offset;
			// ������������
			for (loop = 0; loop < mRange; loop++)
			{
				mTable[loop] = loop;
			}
			// ����������ı�����λ��
			for (loop = 0; loop < mRange; loop++)
			{
				int temp;
				// ʹ�������ѡ��Ҫ�任������
				offset = (rand() % mRange) + loop;
				if (offset >= mRange)
				{
					offset -= mRange;
				}
				// �����ֶԵ�
				temp = mTable[loop];
				mTable[loop] = mTable[offset];
				mTable[offset] = temp;
			}
			mIndex = 0;
		}

	protected:
		unsigned int mRange; // �����ֵ��
		int mIndex; // ȡ������
		int* mTable; // �������
		bool mAutoGenerate; // �Ƿ��Զ����������

	};

}