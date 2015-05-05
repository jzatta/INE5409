

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
    int simulationTime, semaphoreOpenedTime;
    static SortedList<Event> *events;
    static Semaphores *semaphores;
    static int createdCars, destroyedCars;
public:
    int main(int argc, char *argv) {
        // manipulate args
        // seed (random)
        // other 'off simulation' initializations
        return manage();
    }
    
    int manage(){
        int i;
        Event *runningEvt;
        createdCars = destroyedCars = 0;
        events = new SortedList<Event>();
        semaphores = new Semaphores(semaphoreOpenedTime);
        while (true) {
            if (events->empty())
                return -1;
            runningEvt = events->remove(0);
            if (runningEvt->getTime > simulationTime) {
                break;
            }
            runningEvt->handleEvent(); // Event suicide here runningEvt == NULL
        }
        
        // print simulation status
        delete events;
        delete semaphores;
        return 0;
    }
    
    static SortedList<Event> *getEvents() {
        return events;
    }
    
    static Semaphores *getSemaphores() {
        return semaphores;
    }
    
    static void addCreatedCar() {
        createdCars++;
    }
    
    static void addDestroyedCars() {
        destroyedCars++;
    }
}
