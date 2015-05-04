

/*       North
 *         /\
 *  West  <-->  East
 *         \/
 *       South
 */

#define WE_TRACKS 3
#define EW_TRACKS 3
#define NS_TRACKS 4
#define SN_TRACKS 4

class Manager {
private:
    /* use List<Track> 
     * List<Track>
     */
    Track *tracksWE[WE_TRACKS];
    Track *tracksEW[EW_TRACKS];
    Track *tracksNS[NS_TRACKS];
    Track *tracksSN[SN_TRACKS];
    int semOpened, simulationTime;
    bool elapsedTime;
    static SortedList<Event> *events;
public:
    int main(int argc, char *argv) {
        // manipulate args
        // seed (random)
        // other 'off simulation' initializations
        return manage();
    }
    
    int manage(int simTime){
        int i;
        Event *runningEvt;
        events = new SortedList<Event>();
        semOpened = -1;
        elapsedTime = false;
        while (true) {
            if (runningEvt->getTime > simulationTime) {
                break;
            }
            if (events->empty())
                return -1;
        }
        // print simulation status
        delete events;
        return 0;
    }
    
    static SortedList<Event> *getEvents() {
        return events;
    }
}
