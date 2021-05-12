#include "Blocks.h"

Blocks::Blocks(const BlockType& type, Color c)
	:
	StartPos({9, 3})
{
	MovingBlocks.reserve(total);
	Vei2 loc = StartPos;
	if (type == BlockType::I)
	{
		for (int y = 0; y < pysty; y++)
		{
			loc.y += 1;
			for (int x = 0; x < viisto; x++)
			{
				loc.x += 1;
				if (loc.x >= StartPos.x + 3)
				{
					loc.x = StartPos.x;
				}
				int i = y * viisto + x;
				MovingBlocks.emplace_back(loc, c);
				if (x == 0)
				{
					MovingBlocks[i].Empty = false;
				}
				else
				{
					MovingBlocks[i].Empty = true;
				}
				
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

	if (kbd.KeyIsPressed(VK_LEFT) && brd.IsInsideBoard(MostLeftBlockTest()) )
	{
		delta_loc = {-1, 0};
	}
	else if (kbd.KeyIsPressed(VK_RIGHT) )
	{
		delta_loc = { 1, 0 };
	}
	else
	{
		delta_loc = { 0, 0 };
	}
}


Vei2 Blocks::MostLeftBlock() const
{
	Vei2 pos;
	Vei2 temp;
	bool found = false;
	for (int i = 0; i < MovingBlocks.size(); i++)
	{
		if (MovingBlocks[i].Empty)
		{
			continue;
		}
		else
		{
			temp = MovingBlocks[i].GetPos();
			if (!found)
			{
				pos = temp;
				found = true;
			}
			else
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
		}
		
	}
	return pos;
}

Vei2 Blocks::MostLeftBlockTest() const
{
	/*auto it = std::find_if(MovingBlocks.begin(), MovingBlocks.end(), 
		[&] (const BlockSeg& l, const BlockSeg& r)
		{
			return l.GetPos() < r.GetPos();
		});
	return it->GetPos();*/

	auto n = std::min_element(MovingBlocks.begin(), MovingBlocks.end(),
	[] (const BlockSeg& l, const BlockSeg& r)
	{
		
		return l.Empty == false && l.GetPos().x < r.GetPos().x;

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
