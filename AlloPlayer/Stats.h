#pragma once

#include <vector>
#include <boost/chrono/duration.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/thread/mutex.hpp>

class Stats
{
public:
    // events
    void droppedNALU(int type);
    void addedNALU(int type);
    /*void decodedNALU(int type);
    void failedToDecodeNALU(int type);
    void displayedCubemapFace(int face);
    void displayedFrame();*/
    
    // statistical values
    double naluDropRate(boost::chrono::microseconds window,
        boost::chrono::microseconds nowSinceEpoch = boost::chrono::microseconds(0));
    
    // utility
    std::string summary(boost::chrono::microseconds window);
    void autoSummary(boost::chrono::microseconds frequency);

private:
    
    template <typename ValueType>
    class TimeValueDatum
    {
    public:
        TimeValueDatum(ValueType value);
        const boost::chrono::microseconds timeSinceEpoch;
        const ValueType value;
    };
    
    std::vector<TimeValueDatum<int> > droppedNALUs;
    std::vector<TimeValueDatum<int> > addedNALUs;
    
    template <typename ValueType>
    bool isInTime(Stats::TimeValueDatum<ValueType> datum,
        boost::chrono::microseconds window,
        boost::chrono::microseconds nowSinceEpoch);
    
    template <typename Features, typename ValueType>
    boost::accumulators::accumulator_set<Stats::TimeValueDatum<ValueType>, Features>filterTime(
        std::vector<TimeValueDatum<ValueType> >& data,
        boost::chrono::microseconds window,
        boost::chrono::microseconds nowSinceEpoch);
    
    boost::chrono::microseconds nowSinceEpoch();
    
    std::string formatDuration(boost::chrono::microseconds duration);
    
    boost::mutex mutex;
    boost::thread autoSummaryThread;
    void autoSummaryLoop(boost::chrono::microseconds frequency);
};

