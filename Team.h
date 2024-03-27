//
// Created by Gal Ishai on 3/15/24.
//

#ifndef WET_2_TEAM_H
#define WET_2_TEAM_H

#include "AVLRankTree.h"
#include "PlayerByCreated.h"
#include "PlayerByStrength.h"

class Team
{
public:
    int m_teamID;
    int m_wins;
    int m_power;
    AVLRankTree<PlayerByCreated>* m_playersByCreated;
    AVLRankTree<PlayerByStrength>* m_playersByStrength;
    PlayerByStrength* m_medianPlayer;
    explicit Team(int teamID, int wins = 0, int power = 0)
    {
        m_teamID = teamID;
        m_wins = wins;
        m_power = power;
        m_playersByCreated = new AVLRankTree<PlayerByCreated>();
        m_playersByStrength = new AVLRankTree<PlayerByStrength>();
        m_medianPlayer = nullptr;
    }

    virtual ~Team()
    {
        delete m_playersByCreated;
        delete m_playersByStrength;
    }
    virtual bool operator==(Team* other) const = 0;
    virtual bool operator<(Team* other) const = 0;

    void updateMedianAndPower() //TODO
    {
        if(m_playersByStrength->m_treeSize == 0)
        {
            m_medianPlayer = nullptr;
            m_power = 0;
        }
        else
        {
            m_medianPlayer = m_playersByStrength->select(m_playersByStrength->m_root,
                                                         m_playersByStrength->m_treeSize / 2 + 1)->m_info;
            m_power = m_medianPlayer->m_strength * m_playersByStrength->m_treeSize;
        }
    }


};
#endif //WET_2_TEAM_H
