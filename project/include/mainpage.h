/*! \mainpage CSCI 3081 Delivery Simulation project
*
* <h1> Iteration One </h1>
*
* This file is the index for Shane Vadnais' final submission for iteration one of CSCI3081W
* Program Design and Development
*
* <h2>Iteration One UML </h2>
*
* <a href="UML.pdf" target="_blank"><b>First Iteration UML Diagram</b></a>
*
* <h2> Tutoring a New User On Usage of My Code </h2>
*
* In this section, we will run through ways of obtaining my code from the repo I have supplied. I would recommend
* that you begin by finding some way to access the repo by cloning from https://github.umn.edu/umn-csci-3081-s21/repo-vadna034. 
* If a user is on a local machine, they should install docker following the tutorial given in our first lab, build the 
* environment running the script bin/build-env.sh, then the command bin/run-env.sh to enter the docker container.
* In order to get this code running on a cse-labs machine (or a machine which followed the previous steps of downloading
* and configuring Docker), change directories into project, and run the command make. 
* After makefile has finished executing, an executable should exist. To run this executable, use the run script residing
* at location project/bin/run.sh. To create my tests, run the command make test. After compilation, execute the shell script
* at location project/bin/test.sh. 
*
* <h2> A Quick Discussion On Factories </h2>
*
* I chose to implement my factories using the abstract factory pattern. In this pattern, we have factories that  
* implement an abstract factory interface, returning the abstract class IEntity*. This abstract factory design pattern
* was as well used to create a composite factory, which can create any of combination of Drones, Customers, and Packages
*
* I chose to implement using an abstract factory pattern. I chose this pattern, as it allowed me to very easily separate
* the concern of implementing the creation of objects within each factory. If each factory has a single new statement to 
* worry about, then I can easily test the entity using just this factory, and I can easily append more factories by 
* adding a factory who's implementation is one function needing a single new statement. 
*
* Pros of the abstract factory pattern are that it allowed us to implement the composite factory. Because we can add
* many factories of type IEntityFactory* to our vector of factories, we can easily turn on and off the types of entities
* that we want in our simulation. Some cons are that is spreads the logic into many different files, making it hard for us
* to easily see how decisions are being made by the different factories.  
*
* Pros of the factory method pattern are that it centralizes your login into a single factory method. 
* Cons of the factory pattern. Cons are that it is difficult to use anything other than this factory method that has been
* created. If a user wants versatility, and to be able to test different details with the factory, it can 
* become hard to do. 
* 
* <h2> A Note On Extra Credit </h2>
*
* I believe that my code would suffice for the extra credit. It does not actually test for collision detection with other
* drones, but apart from that small piece of logic, it is currently working to accept multiple packages. If that is
* sufficient for the extra credit, please test my code against whatever test-cases are in the extra-credit. 
*
* <h1> Iteration Two </h1>
*
* Group 11: Shane Vadnais, Reka Leeaphon, Aditya Tekale, Muntaqim Mehtaz
*
* <h2>Iteration Two UML </h2>
*
* <a href="UML2.pdf" target="_blank"><b>Second Iteration UML Diagram</b></a>
*
* <h2> Designing and Implementing the routes </h2>
*
* Our design of the different routes used by the drone involves the implementation of the strategy pattern, where we decided to 
* represent the routes as our concrete strategies. Each of these strategies would be implemented in their own way under the shared 
* function. We have the code structured in the following way inside a separate folder called "strategy":
* 
* 1. A Strategy interace that has the virtual function getPath that takes in a deliverer, package and customer object and returns
* the fullpath of the drone from its starting point to the customer
* 2. SmartStrategy, ParabolicStrategy and BeelineStrategy are the concrete strategies that override the base getPath function; each
* implements a different way to get the package delivered to the desired customer 
* 3. We made use of our DeliveryScheduler class from previous deliverables as our context class that calls the strategies based
* on the values associated with the "path" keys represented in the json files for the web scenes 
* 
* An area we found challenging was to fit the strategy pattern to our already existing codebase. From previous iterations, we further
* filtered the DeliverySimulation class to adjust package scheduling and robots as a secondary method of delivery. Since we decided to
* have a deliverer entity, which can be either a drone or a robot, we left room for extension in the future for other modes of delivery.
* So we went ahead and made the DeliveryScheduler our context class that decides which deliverer takes which path. We received clarification
* the course staff about the details of the context class and decided to improvise the class to fit our architecture whilst leaving room 
* for future improvements and features.
*
* <h2> Design of the Observer Pattern </h2>
*
* In writing our observer pattern, we implemented an Observer Subject base class. This class implements the EntityConsoleLogger interface described
* within dependencies in order to create an observer subject. This observer subject consisted of three main portions
*
* <h3> Storage of Observers </h3>
*
* Observers were stored in a set. This set could be appended to, and removed from using the value AddObserver and RemoveObserver functions defined within the 
* ObserverSubject class. These functions were called within delivery_simulation upon within the functions AddObserver and RemoveObserver within that class. 
*
* <h3> Helper Functions to Build Notification PicoJSON's </h3>
*
* Two helper functions were built to build notification that would be used within notify. These functions built notifications with type "notify", "value" specified
* by an argument, and an optional path parameter used for when package carriers begin to move. 
*
* <h3> A notify function </h3>
*
* This function would be used to notify all of the observers of the subjects of the event occuring. Each class was used to create its own notification so that is could
* easily reference itself when calling ObserverSubject's notify, however a different possible implementation would involve passing this as a parameter to the notify functions.
*
* <h2> Minutes of the Meeting </h2>
*
* In this section, we will talk about the team's various meetings that occured over the past three weeks for the succesful
* completion of the project by the deadline assigned.
*
* The team's communication and meetings were held on discord.
*
* All the teammembers actively participated in communicating frequently and making it on time for the meetings.
*
* The first team meeting was held on the 26th of March at 8 PM CST, wherein the team members agreed upon the tasks 
* to be performed and the internal due dates for the same. The team members also agreed upon checking in on each 
* other regularly to keep a track in the progress made as well as guide each other in case of 
* obstacles faced in the completion of the respective tasks. We took up different roles and assigned ourselves 
* each priorities to work on.
*
* Roles: \n Development Lead: Reka Leeaphon (leeap001) \n Scheduler: Aditya Tekale (tekal005) \n Reporter: Muntaqim Mehtaz (mehta216) \n Project Manager: Shane Vadnais (vadna034)
*
* Priority 1 was worked on by Reka Leeaphon, \n Priority 2 was worked on by Shane Vadnais, \n Priority 3 was worked on by Muntaqim Mehtaz and \n Priority 4 was worked on by Aditya Tekale.
* 
* The second meeting was held on the 31st of March at 8PM CST, where the team members checked in on the progress 
* being made on the obsever pattern and the google tests, there was a significant amount of progress 
* made and we decided to meet up again on 1st April to push the work done on the devel branch.
*
* Third meeting was held on the 1st of April at 6PM CST, the tasks assigned to complete the observer pattern were completed        succesfully, however, the google unit testing needed some more time as the number of tests to be written were a 
* plenty. Upon completion of these unit tests, the team decided to make the final push to
* the devel branch of the Team's GitHub repo on the 2nd of April.
* 
* Fourth meeting was held on the 12th of April at 8PM CST, two of the priorities assigned were completed 
* with some changes left to do in google tests, in this meeting, we spoke about the rest two priorities 
* implementation and soft deadlines to get these done.
*
* Fifth meeting was held on 14th of April at 7PM CST, significant progress was been made on the priorities but we still had some   bugs to work on and the team decided to meet again on 16th of April
* 
* Sixth meeting was held on the 16th of April at 5PM CST, the strategy pattern was successfully implemented 
* but documenting the code was left to do, the battery implementation still had some bugs which was 
* fixed by collaborating with the team members, google tests were being written and some of the 
* tests to implement were still left to do.
*
* Seventh meeting was held on 19th of April at 10AM CST, all our priorities have been implemented successfully 
* we decided to do a push to the devel branch later at 5PM CST and then  make the final push to master branch 
* once we check our working code on the CSELab machine. 
*
*
*
* <h1> Iteration Three </h1>
*  The new feature implemented which is the "Entity color decorator" works on all the scenes in the simulation.
*
* <h2> Iteration three UML </h2>
*
* <a href="UML3.pdf" target="_blank"><b>Third Iteration UML Diagram</b></a>
*
* <h2> Developer Documentation </h2>
* In this section, we will run through ways of obtaining the code from the repo we have supplied. We would recommend
* that you begin by cloning the repo. \n
* 1. If a user is on a local machine, they should install docker following the tutorial given in our first lab, build the 
* environment running the script bin/build-env.sh, then the command bin/run-env.sh to enter the docker container. \n
* 2. In order to get this code running on a cse-labs machine (or a machine which followed the previous steps of downloading
* and configuring Docker), change directories into project, and run the command make. \n 
* 3. After makefile has finished executing, an executable should exist. To run this executable, use the run script residing
* at location project/bin/run.sh. To create our tests, run the command make test. After compilation, execute the shell script
* at location project/bin/test.sh. \n
* 4. To run a specific scene on the simulation, use the run script as follows in the terminal from project directory, 
* ./bin/run.sh /scenes/all_features.json (any json scene that exists in the scenes directory could be used in 
* place of all_features.json) \n
* 5. Once all of this is done, the server starts and you need to open either chrome or firefox and 
* input the URL http://127.0.0.1:8081/
* Once the website opens up, the simulation is played, you can speed up the simulation or choose an entity to look at or show all
* routes or current route. \n
* Once you are done and want to kill the simulation or if the simulation is executed succesfully, either kill simulation on
* website itself or use Ctrl+C (windows) or Cmd+C (mac) in the terminal to kill the simulation.
*
* <h2> Short description of Pattern Used </h2>
* We chose to implement the decorator pattern to add color to the entities which are the robot and the drone entity.
* In this implementation we extended the drone factory and robot factory that creates the colored
* robot/drone if and only if the picojson object contains a 'color' key and the value is set to 'true'. Further, we also created a DecoratorInterface 
* which is used as a blueprint in the DecoratedCarrier and implements the update function in such a way that when the simulation runs, the color of the entity
* starts to change as the entity moves and battery depletes. To test this functionality, we added a JSON field called "colored" in all_features_no_recharge.json 
* for one robot and one drone. This value was set to 'true' to color these entities in the simulation.
*
* <a href="DecoratorPattern.pdf" target="_blank"><b>Decorator Pattern UML</b></a>
*
* <h2> Discussion on the design pattern </h2>
* The pattern we chose to implement in this feature was the decorator pattern since compared to the other patterns, the decorator
* pattern has an advantage in this feature of adding colors to the multiple entities in the simulation, so essentially we were able to 'decorate' our entities.
* Using decorator pattern provides us with a flexibility which allows to develop a series of fuctionality from a specific targeted
* class instead of coding all the behavior into the object.
*
* Advantages: - By using decorator pattern we can use the objects any number of times as needed as both the target
* objects and decorators follow the same interface.
*
* Difficulty faced while working on the feature: - One of the main difficulties faced in implementing the feature was working
* on the notifications to work correctly for drone and robot in the simulation; another area of difficulty was faced while creating 
* the drone decorator method to fit in with the updated movement functionality. Once it was figured out, the rest of the implementation got a bit easier.
*
* <h2> Teammates Documentation </h2>
* First team meeting was held on 26th of April at 5PM where we decided on which feature would be best to 
* implement for iteration 3
*
* Second meeting was held on 27th of April at 8PM where we talked about how to implement the decorator pattern 
* and how to change colors upon battery usage
*
* Third meeting was held on 28th of April at 9PM, we had the running code implemented and spoke about 
* working on google tests and documenting code and working on updating the UML as needed.
*
* Fourth meeting was held on 29th of April at 10AM, in this meeting we checked up on the progress we've made so far.
*
* Each team member has been assigned a task while working on this iteration; \n
* Shane Vadnais: Assigned to work on writing the code for the new feature \n
* Muntaqim Mehtaz: Assigned to work on UML diagram and office hours to get questions answered \n
* Aditya Tekale: Assigned to work on documenting whatever is needed \n
* Reka leeaphon: Assigned to work on updating the google tests.
*/
