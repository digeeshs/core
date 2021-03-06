//
//  peer_dbs.h - Data Broadcasting Set of rules.
//
//  This code is distributed under the GNU General Public License (see
//  the THE_GNU_GENERAL_PUBLIC_LICENSE.txt file for extending this
//  information).  Copyright (C) 2016, the P2PSP team.
//
//  http://www.p2psp.org
//

#ifndef P2PSP_CORE_PEER_DBS_H
#define P2PSP_CORE_PEER_DBS_H

#include "peer_core.h"

using namespace boost::asio;

namespace p2psp {

  class Peer_DBS : public Peer_core {
  protected:
    static const int kMaxChunkDebt = 128;  // Peer's rejecting threshold

    int kAddr = 0;
    int kPort = 1;

    std::map<ip::udp::endpoint, int> debt_;

    int number_of_monitors_;
    int max_chunk_debt_;

    int receive_and_feed_counter_;
    std::vector<char> receive_and_feed_previous_;

    int debt_memory_;
    bool waiting_for_goodbye_;
    bool modified_list_;
    std::vector<ip::udp::endpoint> peer_list_;
    int number_of_peers_;
    bool ready_to_leave_the_team_;

  public:
    Peer_DBS();
    ~Peer_DBS();
    virtual void Init() override;
    virtual void SayHello(const ip::udp::endpoint&);
    virtual void SayGoodbye(const ip::udp::endpoint&);
    virtual void ReceiveTheListOfPeers();
    void ReceiveTheNumberOfPeers();
    void ListenToTheTeam()/* override*/;
    virtual int ProcessMessage(const std::vector<char>&,
                               const ip::udp::endpoint&) override;
    virtual float CalcBufferCorrectness();
    virtual float CalcBufferFilling();
    virtual void PoliteFarewell();
    virtual void BufferData() override;
    virtual void Start() override;
    virtual void Run() override;
    virtual void ConnectToTheSplitter() throw(boost::system::system_error) override;
    bool AmIAMonitor();

    int GetNumberOfPeers();
    virtual void SetMaxChunkDebt(int);
    virtual int GetMaxChunkDebt();
    virtual std::vector<ip::udp::endpoint> *GetPeerList();
    static int GetDefaultMaxChunkDebt();
    virtual void ReceiveMyEndpoint();
    virtual bool IsReadyToLeaveTheTeam();
  };
}

#endif  // P2PSP_CORE_PEER_DBS_H
