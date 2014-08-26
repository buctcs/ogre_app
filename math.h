/**
Math:
@description: This section includes math methods created for Final Engine, 
	i.e., the one to produce random numbers.
@created: 2013.8.28
@author: 贾林林
@reference:
	1. 游戏程序设计概论, P97-102, 
*/

#include "stdafx.h"
#include <time.h>
namespace FinalEngine
{

	/** 
	随机数产生类（预先建立随机数表方式）:
	此类能产生一个值域范围内的随机正整数，符合平均分布，
	即连续一次值域数量的随机数时，各数精确出现1次；超过
	值域数量且自动重置为false时需要重置随机数表。
	*/
	class RandomNum
	{
	public:
		RandomNum(unsigned int Range, bool AutoGen = false)
			: mRange(Range), mTable(NULL), mIndex(0), mAutoGenerate(AutoGen)
		{
			srand((unsigned)time(NULL)); // 使用时间产生随机数字
			mRange = Range;
			mTable = new int [mRange];
			Generate(); // 产生随机数
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

		// 取出随机数
		int GetNumber(void)
		{
			int number = -1;
			if (mRange > 0)
			{
				number = mTable[mIndex]; // 取出随机数
				++mIndex;
				if (mIndex >= mRange)
				{
					mIndex = 0;
					if (mAutoGenerate) // 重新产生随机数
					{
						Generate();
					}
				}
			}
			return number;
		}

		// 随机数重整
		void Generate(void)
		{
			int loop, offset;
			// 建立连续数字
			for (loop = 0; loop < mRange; loop++)
			{
				mTable[loop] = loop;
			}
			// 依照随机数改变数字位置
			for (loop = 0; loop < mRange; loop++)
			{
				int temp;
				// 使用随机数选择要变换的数字
				offset = (rand() % mRange) + loop;
				if (offset >= mRange)
				{
					offset -= mRange;
				}
				// 将数字对调
				temp = mTable[loop];
				mTable[loop] = mTable[offset];
				mTable[offset] = temp;
			}
			mIndex = 0;
		}

	protected:
		unsigned int mRange; // 随机数值域
		int mIndex; // 取出索引
		int* mTable; // 随机数表
		bool mAutoGenerate; // 是否自动产生随机数

	};

}