////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "SmartMove.h"

#include <queue>

////////////////////////////////////////////////////////////
SmartMove::SmartMove()
	: m_pathExist(false)
{
}


////////////////////////////////////////////////////////////
void SmartMove::BFS(const std::shared_ptr<Tile>& source, const std::shared_ptr<Tile>& target)
{
	m_tree.clear();
	m_source = source; // the robot
	m_target = target; // the enemy
	std::queue<std::weak_ptr<Tile>> Q;
	m_source->m_status = IN_PROGRES;
	m_source->m_discovery = 0;
	m_tree.push_back(m_source);
	Q.push(m_source);

	while (!Q.empty()) {
		auto u = Q.front().lock();
		if (u == m_target) {
			m_pathExist = true;
			u->m_status = VISTED;
			break;
		}
		Q.pop();

		for (const auto& vertex : u->m_adjacencyList) {
			auto v = vertex.second.lock();
			if (v->isEmpty() && v->m_status == NOT_VISTED) {
				v->m_status = IN_PROGRES;
				v->m_discovery = u->m_discovery + 1;
				v->m_parent = u;
				m_tree.push_back(v);
				Q.push(v);
			}
		}
		u->m_status = VISTED;
	}
}


////////////////////////////////////////////////////////////
bool SmartMove::pathExist() const
{
	return m_pathExist;
}


////////////////////////////////////////////////////////////
Direction SmartMove::getDirection()
{
	auto direction = STAND;
	std::vector<std::weak_ptr<Tile>>::iterator start = std::find_if(m_tree.begin(), m_tree.end(),
		[&](const auto& v)
	{
		return v.lock()->getRect() == m_target->getRect();
	});
	if (start != m_tree.end()) {
		auto wanteDirection = (*start).lock();
		if (wanteDirection && wanteDirection->m_parent) {
			if (wanteDirection->m_parent->m_rect.left > m_target->m_rect.left) direction = RIGHT;
			if (wanteDirection->m_parent->m_rect.left < m_target->m_rect.left) direction = LEFT;
			if (wanteDirection->m_parent->m_rect.top > m_target->m_rect.top) direction = DOWN;
			if (wanteDirection->m_parent->m_rect.top < m_target->m_rect.top) direction = UP;
		}
	}
	return direction;
}
