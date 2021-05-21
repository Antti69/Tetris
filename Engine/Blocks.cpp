#include "Blocks.h"

/*Blocks::Blocks(const BlockType& type, Color c)
	:
	StartPos({9, 3}),
	type(type)
{
	MovingBlocks.reserve(total);		
	Vei2 loc = StartPos;
	for (int y = 0; y < pysty; y++)
	{
		loc.y += 1;
		for (int x = 0; x < viisto; x++)
		{
			loc.x += 1;
			MovingBlocks.emplace_back(loc, c);
			if (loc.x >= StartPos.x + viisto)
			{
				loc.x = StartPos.x;
			}
			int i = y * viisto + x;
			
			if (type == BlockType::I)
			{
				if (x == 1)
				{
					MovingBlocks[i].Empty = false;
				}
			}
			if (type == BlockType::L)
			{
				if ((x == 1 && y != 3) || i == 0)
				{
					MovingBlocks[i].Empty = false;
				}
			}


		}
	}

}*/

Blocks::Blocks(const BlockType& type, Color c)
	:
	StartPos({9, 3}),
	type(type)
{
	
	Vei2 loc = StartPos;

	if (type == BlockType::I)		//2D Grid
	{
		MovingBlocks.reserve(total);
		for (int y = 0; y < Collums; y++)
		{
			loc.y += 1;
			for (int x = 0; x < Rows; x++)
			{
				loc.x += 1;
				MovingBlocks.emplace_back(loc, c);
				if (loc.x >= StartPos.x + Rows)
				{
					loc.x = StartPos.x;
				}
				int i = y * Rows + x;
				if (x == 1)
				{
					MovingBlocks[i].Empty = false;
				}
			}
		}
	}
	else
	{
		MovingBlocks.reserve(Linerialtotal);			//Linerial Grid for easier rotation
		for (int i = 0; i < top; i++)					// 0  1  2
		{												// 7  8  3
			loc.x += 1;									// 6  5  4
			MovingBlocks.emplace_back(loc, c);
		}
		for (int t = 0; t < right; t++)
		{
			loc.y += 1;
			MovingBlocks.emplace_back(loc, c);
		}
		for (int k = 0; k < bottom; k++)
		{
			loc.x -= 1;
			MovingBlocks.emplace_back(loc, c);
		}
		loc.y -= 1;
		for (int j = 0; j < leftandmidlle; j++)
		{
			MovingBlocks.emplace_back(loc, c);
			loc.x += 1;
		}
		for (int i = 0; i < Linerialtotal; i++)
		{
			if (type == BlockType::L && (i == 0 || i == 1 || i == 5 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
			if (type == BlockType::Brick && (i == 0 || i == 1 || i == 7 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
			if (type == BlockType::HalfCross && (i == 1 || i == 5 || i == 7 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
			if (type == BlockType::N && (i == 2 || i == 3 || i == 5 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
			if (type == BlockType::MirrorN && (i == 0 || i == 5 || i == 7 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
			if (type == BlockType::MirrorL && (i == 1 || i == 2 || i == 5 || i == 8))
			{
				MovingBlocks[i].Empty = false;
			}
		}
	}


}

void Blocks::Draw(Board& brd) const
{
	for (auto& s : MovingBlocks)
	{
		if (!s.Empty)
		{
			s.Draw(brd);
		}
	}
}

void Blocks::MoveBy(Vei2& delta_loc)
{
	for (auto& s : MovingBlocks)
	{
		s.Moveby(delta_loc);
	}
}

void Blocks::Movement(Vei2& delta_loc, Keyboard& kbd, const Board& brd)
{
	const Keyboard::Event e = kbd.ReadKey();
	if (kbd.KeyIsPressed(VK_LEFT) && brd.IsInsideBoard(MostSideBlock('l') += {-1, 0}))
	{
		delta_loc = { -1, 1 };
		if (e.IsPress() && e.GetCode() == VK_UP)
		{
			Rotate();
		}
	}
	else if (kbd.KeyIsPressed(VK_RIGHT) && brd.IsInsideBoard(MostSideBlock('r') += {1, 0}))
	{
		delta_loc = { 1, 1 };
		if (e.IsPress() && e.GetCode() == VK_UP)
		{
			Rotate();
		}
	}
	else if (e.IsPress() && e.GetCode() == VK_UP)
	{
		Rotate();
	}
	else
	{
		delta_loc = { 0, 0 };
	}
	PositionFix(brd);
}

void Blocks::PositionFix(const Board& brd)
{
	if (!brd.IsInsideBoard(MostSideBlock('r')))
	{
		MoveBy(Vei2(-1, 0));
	}
	if (!brd.IsInsideBoard(MostSideBlock('l')))
	{
		MoveBy(Vei2(1, 0));
	}
}

void Blocks::Rotate()
{
	if (type == BlockType::I)
	{
		std::swap(MovingBlocks[1].Empty, MovingBlocks[4].Empty);
		std::swap(MovingBlocks[9].Empty, MovingBlocks[6].Empty);
		std::swap(MovingBlocks[13].Empty, MovingBlocks[7].Empty);
	}
	else if (type == BlockType::Brick)
	{

	}
	else
	{
		std::vector<BlockSeg> temp;
		std::rotate_copy(MovingBlocks.begin(), MovingBlocks.begin() + 2, MovingBlocks.end() - 1, std::back_inserter(temp));
		for (int i = 0; i < temp.size(); i++)
		{
			MovingBlocks[i].pos = temp[i].pos;
		}
	}
}



Vei2 Blocks::MostSideBlock(const char m) const
{
	Vei2 pos;
	Vei2 temp;
	bool FirstActive = false;
	for (int i = 0; i < MovingBlocks.size(); i++)
	{
		if (MovingBlocks[i].Empty)
		{
			continue;
		}
		else
		{
			temp = MovingBlocks[i].GetPos();
			if (!FirstActive)
			{
				pos = temp;
				FirstActive = true;
			}
			else
			{
				if (m == 'l')
				{
					if (temp.x < pos.x)
					{
						pos = temp;
					}
					else
					{
						pos = pos;
					}
				}
				if (m == 'r')
				{
					if (temp.x > pos.x)
					{
						pos = temp;
					}
					else
					{
						pos = pos;
					}
				}
			}
		}
		
	}
	return pos;
}


Vei2 Blocks::MostLeftBlockTest()
{
	std::vector<BlockSeg> test;
	std::copy_if(MovingBlocks.begin(), MovingBlocks.end(), std::back_inserter(test),
		[] (BlockSeg& l)
		{
			return l.Empty == false;
		});

	auto n = std::min_element(test.begin(), test.end(),
		[] (BlockSeg& l, BlockSeg& r)
		{
			return l.GetPos().x < r.GetPos().x;
		});

	return n->GetPos();
}



Blocks::BlockSeg::BlockSeg(Vei2& in_pos, Color c)
	:
	pos(in_pos),
	BColor(c)
{
}

void Blocks::BlockSeg::Draw(Board& brd) const
{
	brd.DrawCell(pos, BColor);
}

void Blocks::BlockSeg::Moveby(Vei2& delta_loc)
{
	pos += delta_loc;
}

Vei2 Blocks::BlockSeg::GetPos() const
{
	return pos;
}
