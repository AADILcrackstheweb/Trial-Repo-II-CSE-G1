'''
# Course-Scheduling
The Course Scheduling App is a Python application built using the tkinter library and MySQL database to manage course scheduling for a university or educational institution. It allows users to add rooms, courses, and timings, and then generates a timetable based on input data. This project, originally, was implemented in C++ with file inputs and terminal interaction. We aimed to upgrade the system by implementing GUI and database interaction using Python.

## Prerequisites

Before running the application, make sure you have the following prerequisites installed:

- Python 3.10.10
- tkinter (usually included in Python standard library)
- MySQL Connector (`mysql-connector-python`)

You should also have a MySQL database server set up with a database named "course" (you can change the database name in the code if needed).

## Getting Started
1. Clone this repository to your local machine: `git clone https://github.com/HarSen0604/course-scheduling-app.git`
2. Install the required Python packages
   2.1. `pip3.10 install mysql-connector-python`
   2.2. `pip3.10 install re`
3. Enter the details of the MySQL database in the Python code. Defined in the `__init__` of the class `CourseSchedulingApp`.
4. Run the application: `python3.10 CourseSchedulingApp.py`.
5. Follow the on - screen instructions.

## Usage:
1. Add Rooms: Enter room numbers and capacities. The app validates input and ensures constraints are met.
   1.1. Constraints:
     1.1.1. Room numbers are in three digit format.
     1.1.2. The building can have a maximum of 20 rooms.
     1.1.3. Room capacities are within the range [10, 300]
2. Add Courses: Enter course codes in the format 'csddd' (e.g., cs101). The app validates input and checks for duplicates.
3. Add Timings: Enter time slots (e.g., MWF1, TT2:30). The app validates input and checks for duplicates.
   3.1. Constraints:
     3.1.1. Valid lecture times are of the form “MWFd” or “MWFdd” or “TTd” or “TTd:dd” or “TTdd:dd”.
     3.2.2. There are no more than 15 such valid lecture times.
4. Submit: Displays tables with added rooms, courses, and timings.
5. Course Scheduling 2:
   5.1. Contains details about the courses that are being given. It lists the course number, anticipated enrollment, and a selection of preferred lecture times for each individual course. A post-graduate course is one with a course number greater than 600; all other courses are undergraduate.
   5.2. `Enrollment` are integers in the range [3..250].
   5.3. `Preferences` are time preferences of the instructor, separated by commas (a maximum of 5 preferences are allowed for a course).
6. Generate Time Table: Generates a course timetable based on added data and displays it in a new window.
7. Exception Window: The exceptions are displayed in this window.

'''

import tkinter as tk
import mysql.connector as mc
import re
from tkinter import messagebox, ttk

class Room:
    def __init__(self, roomNo, cap):
        self.roomNo = roomNo
        self.cap = cap

class Course:
    def __init__(self, courseCode):
        self.courseCode = courseCode

class Time:
    def __init__(self, timing):
        self.timing = timing

class Input2:
    def __init__(self, courseCode, enrollment, preferences, graduate):
        self.courseCode = courseCode
        self.enrollment = enrollment
        self.preferences = preferences
        self.graduate = graduate

class CourseSchedulingApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Course Scheduling")

        # Connect to the MySQL database
        self.db_connection = mc.connect(
            host="",        # When running on your local machine, use `localhost` else enter the host accordingly
            user="",        # Enter your username, usually `root`
            password="",    # Enter your password used for MySQL
            database=""     # Enter the database used by the application
        )

        # Create a cursor object to interact with the database
        self.db_cursor = self.db_connection.cursor()

        # Create tables if they don't exist
        self.create_tables()

        # Room and Capacity
        self.room_label = tk.Label(root, text="Room: ")
        self.room_label.pack()
        self.room_entry = tk.Entry(root)
        self.room_entry.pack()
        self.capacity_label = tk.Label(root, text="Capacity: ")
        self.capacity_label.pack()
        self.capacity_entry = tk.Entry(root)
        self.capacity_entry.pack()
        self.add_room_button = tk.Button(root, text="Add Room and Capacity", command=self.add_room_capacity)
        self.add_room_button.pack()

        # Course
        self.course_label = tk.Label(root, text="Course: ")
        self.course_label.pack()
        self.course_entry = tk.Entry(root)
        self.course_entry.pack()
        self.add_course_button = tk.Button(root, text="Add Course", command=self.add_course)
        self.add_course_button.pack()

        # Times
        self.time_label = tk.Label(root, text="Times: ")
        self.time_label.pack()
        self.time_entry = tk.Entry(root)
        self.time_entry.pack()
        self.add_time_button = tk.Button(root, text="Add Time", command=self.add_time)
        self.add_time_button.pack()

        # Submit Button
        self.submit_button = tk.Button(root, text="Submit", command=self.display_tables)
        self.submit_button.pack()

        # Labels to display table contents
        self.rooms_label = tk.Label(root, text="Rooms and Capacities: ")
        self.rooms_label.pack()
        self.courses_label = tk.Label(root, text="Courses: ")
        self.courses_label.pack()
        self.timings_label = tk.Label(root, text="Timings: ")
        self.timings_label.pack()

        # Create a new window for input2
        self.input2_window = None

        # Create a list of objects
        self.listRoom = []
        self.listCourse = []
        self.listTime = []
        self.listInput2 = []

    def create_tables(self):
        # Define the SQL queries to drop and then create the tables
        drop_room_table_query = "DROP TABLE IF EXISTS rooms"
        drop_course_table_query = "DROP TABLE IF EXISTS courses"
        drop_time_table_query = "DROP TABLE IF EXISTS timings"
        drop_input2_table_query = "DROP TABLE IF EXISTS input2"

        # Execute the SQL queries to drop the tables
        self.db_cursor.execute(drop_room_table_query)
        self.db_cursor.execute(drop_course_table_query)
        self.db_cursor.execute(drop_time_table_query)
        self.db_cursor.execute(drop_input2_table_query)

        # Define the SQL queries to create the tables if they don't exist
        create_room_table_query = """
        CREATE TABLE rooms (
            room_id INT AUTO_INCREMENT PRIMARY KEY,
            room_number VARCHAR(3) UNIQUE,
            capacity INT CHECK (capacity BETWEEN 10 AND 300)
        )
        """
        
        create_course_table_query = """
        CREATE TABLE courses (
            course_id INT AUTO_INCREMENT PRIMARY KEY,
            course_code VARCHAR(10) UNIQUE
        )
        """
        
        create_time_table_query = """
        CREATE TABLE timings (
            time_id INT AUTO_INCREMENT PRIMARY KEY,
            time_slot VARCHAR(10) UNIQUE
        )
        """

        # Create 'input2' table if it doesn't exist
        create_input2_table_query = """
        CREATE TABLE IF NOT EXISTS input2 (
            course_code VARCHAR(10) PRIMARY KEY,
            enrollment INT,
            preferences VARCHAR(255),
            graduate VARCHAR(2)
        )
        """
        
        # Execute the SQL queries
        self.db_cursor.execute(create_room_table_query)
        self.db_cursor.execute(create_course_table_query)
        self.db_cursor.execute(create_time_table_query)
        self.db_cursor.execute(create_input2_table_query)
        
        # Commit the changes to the database
        self.db_connection.commit()

    def add_room_capacity(self):
        room = self.room_entry.get()
        capacity = self.capacity_entry.get()

        # Define a flag to track whether there's an error
        has_error = False

        # Check constraints for 'room' and 'capacity'
        if not (room.isdigit() and 100 <= int(room) <= 999):
            messagebox.showwarning("Invalid Room", "Room number must be three digits.")
            has_error = True

        if not (capacity.isdigit() and 10 <= int(capacity) <= 300):
            messagebox.showwarning("Invalid Capacity", "Capacity must be between 10 and 300.")
            has_error = True

        # If there's no error, check if the number of rooms in the database is less than or equal to 20
        if not has_error:
            count_query = "SELECT COUNT(*) FROM rooms"
            self.db_cursor.execute(count_query)
            count = self.db_cursor.fetchone()[0]

            if count >= 20:
                messagebox.showwarning("Room Limit Exceeded", "The maximum number of rooms (20) has been reached.")
            else:
                insert_query = "INSERT INTO rooms (room_number, capacity) VALUES (%s, %s)"
                values = (room, capacity)
                try:
                    self.db_cursor.execute(insert_query, values)
                    self.db_connection.commit()
                except mc.IntegrityError as e:
                    messagebox.showwarning("Duplicate Entry", "This room already exists in the database.")

            # Clear the entry fields
            self.room_entry.delete(0, tk.END)
            self.capacity_entry.delete(0, tk.END)

    def add_course(self):
        course = self.course_entry.get()

        # Define a flag to track whether there's an error
        has_error = False

        # Check constraints for 'course'
        if not re.match(r'^cs[0-9]{3}$', course):
            messagebox.showwarning("Invalid Course", "Course format must be 'csddd'.")
            has_error = True

        # If there's no error, insert data into the 'courses' table
        if not has_error:
            count_query = "SELECT COUNT(*) FROM courses"
            self.db_cursor.execute(count_query)
            count = self.db_cursor.fetchone()[0]

            if count >= 30:
                messagebox.showwarning("Course Limit Exceeded", "The maximum number of courses (30) has been reached.")
            else:
                insert_query = "INSERT INTO courses (course_code) VALUES (%s)"
                values = (course,)
                try:
                    self.db_cursor.execute(insert_query, values)
                    self.db_connection.commit()
                except mc.IntegrityError as e:
                    messagebox.showwarning("Duplicate Entry", "This course code already exists in the database.")

            # Clear the entry field
            self.course_entry.delete(0, tk.END)

    def add_time(self):
        time = self.time_entry.get()

        # Define a flag to track whether there's an error
        has_error = False

        # Check constraints for 'time'
        if time and not re.match(r'^(MWF[0-9]{1,2}|TT[0-9]{1,2}(:[0-9]{2})?)$', time):
            messagebox.showwarning("Invalid Time", "Invalid time format.")
            has_error = True

        # If there's no error, check if the number of entries in the 'timings' table is less than or equal to 15
        if not has_error:
            count_query = "SELECT COUNT(*) FROM timings"
            self.db_cursor.execute(count_query)
            count = self.db_cursor.fetchone()[0]

            if count >= 15:
                messagebox.showwarning("Time Slots Limit Exceeded", "The maximum number of time slots (15) has been reached.")
            else:
                insert_query = "INSERT INTO timings (time_slot) VALUES (%s)"
                values = (time,)
                try:
                    self.db_cursor.execute(insert_query, values)
                    self.db_connection.commit()
                except mc.IntegrityError as e:
                    messagebox.showwarning("Duplicate Entry", "This lecture time already exists in the database.")

            # Clear the entry field
            self.time_entry.delete(0, tk.END)

    def dummy(self):
    # Call the methods to display the Time Table and Exception List
        self.display_input2()
        self.generate_time_table()
    
    def open_input2_window(self):
        self.input2_window = tk.Toplevel(self.root)
        self.input2_window.title("Course Scheduling 2")

        # Create labels and entry fields for 'input2' data
        self.course_code_label = tk.Label(self.input2_window, text="Course Code: ")
        self.course_code_label.pack()
        self.course_code_entry = tk.Entry(self.input2_window)
        self.course_code_entry.pack()

        self.enrollment_label = tk.Label(self.input2_window, text="Enrollment: ")
        self.enrollment_label.pack()
        self.enrollment_entry = tk.Entry(self.input2_window)
        self.enrollment_entry.pack()

        self.preferences_label = tk.Label(self.input2_window, text="Preferences: ")
        self.preferences_label.pack()
        self.preferences_entry = tk.Entry(self.input2_window)
        self.preferences_entry.pack()

        # Add button to insert 'input2' data into the database
        self.add_input2_button = tk.Button(self.input2_window, text="Add", command=self.add_input2)
        self.add_input2_button.pack()

        # Labels to display 'input2' data
        self.input2_data_label = tk.Label(self.input2_window, text="Data: ")
        self.input2_data_label.pack()
        self.input2_data_text = tk.Text(self.input2_window, height=10, width=40)
        self.input2_data_text.pack()

        # Button to display 'input2' data
        self.display_input2_button = tk.Button(self.input2_window, text="Submit", command=lambda:self.dummy())  # Change here
        self.display_input2_button.pack()

    def generate_time_table(self):
        # Fetch data from 'input2' table and sort by graduate (PG first), and then by priority
        self.db_cursor.execute("SELECT * FROM input2 ORDER BY graduate DESC, preferences")
        input2_data = self.db_cursor.fetchall()
        for row in input2_data:
            courseCode = row[0]
            enrollment = row[1]
            preferences = row[2]
            graduate = row[3]

            # Check if the courseCode from Input2 exists in the list of Course objects
            if not any(course.courseCode == courseCode for course in self.listCourse):
                exception_message = f"{courseCode}: Course not found in the list of Courses."
                self.exception_list.append(exception_message)  # Append to the exception list
                continue

            # Check if preferences are valid time slots
            # Check if the preferences (time slots) from Input2 exist in the list of Time objects
            preference_slots = [] if not preferences else preferences.split(',')
            invalid_preferences = [slot for slot in preference_slots if not any(time.timing == slot for time in self.listTime)]

            if invalid_preferences:
                exception_message = f"{courseCode}: Invalid time slot(s) in preferences: {', '.join(invalid_preferences)}."
                self.exception_list.append(exception_message)  # Append to the exception list
                continue

            input2_instance = Input2(courseCode, enrollment, preferences, graduate)
            self.listInput2.append(input2_instance)

        # Initialize time table
        time_table = {}
        for room in self.listRoom:
            for time in self.listTime:
                time_table[(time.timing, room.roomNo)] = None
        print(time_table)

        # Initialize exception list
        exception_list = []

        # Iterate through the four categories: PG courses with preferences, PG courses without preferences,
        # UG courses with preferences, and UG courses without preferences
        for grad_category in ['PG', 'UG']:
            for pref_status in ['WITH', 'WITHOUT']:
                # Filter courses based on graduate category and preference status
                filtered_courses = [row for row in self.listInput2 if row.graduate == grad_category and
                                    (pref_status == 'WITH' and row.preferences or pref_status == 'WITHOUT' and not row.preferences)]

                # Schedule courses in the specified category
                for row in filtered_courses:
                    course_code, enrollment, preferences, graduate = row.courseCode, row.enrollment, row.preferences, row.graduate
                    scheduled = False

                    # Split preferences into a list
                    preferred_slots = [] if not preferences else preferences.split(',')

                    # Iterate through preferred time slots and rooms
                    for preferred_slot in preferred_slots:
                        if scheduled:
                            break

                        for room in self.listRoom:
                            print(f"Checking slot: {preferred_slot}, room: {room.roomNo}")
                            if scheduled:
                                break

                            # Check if the preferred slot is available and meets enrollment and room capacity requirements
                            key = (preferred_slot, room.roomNo)
                            if key in time_table and time_table[key] is None and enrollment <= room.cap:
                                time_table[key] = course_code
                                scheduled = True
                                break

                    # If the course couldn't be scheduled based on preferences, allocate based on empty seats alone
                    if not scheduled:
                        for room in self.listRoom:
                            if scheduled:
                                break

                            for time in self.listTime:
                                # Check if the slot is available and meets enrollment and room capacity requirements
                                if time_table[(time.timing, room.roomNo)] is None and enrollment <= room.cap:
                                    time_table[(time.timing, room.roomNo)] = course_code
                                    scheduled = True
                                    break

                    if not scheduled:
                        # Add course to exception list if no suitable slot is found
                        exception_list.append(f"{course_code}: No suitable slot available")

        # Create Time Table window and Exception List window
        self.create_time_table_window(time_table, self.listRoom, self.listTime)
        self.create_exception_list_window(exception_list)

    def add_input2(self):
        course_code1 = self.course_code_entry.get()
        enrollment1 = self.enrollment_entry.get()
        preferences1 = self.preferences_entry.get()

        # Define a flag to track whether there's an error
        has_error = False

        # Check constraints for 'course_code' and 'enrollment'
        if not re.match(r'^cs[0-9]{3}$', course_code1):
            messagebox.showwarning("Invalid Course Code", "Course code format must be 'csddd'.")
            has_error = True

        if not enrollment1:
            messagebox.showwarning("Enrollment Missing", "Enrollment is required.")
            has_error = True
        elif not enrollment1.isdigit() or not (3 <= int(enrollment1) <= 250):
            messagebox.showwarning("Invalid Enrollment", "Enrollment must be an integer in the range [3..250].")
            has_error = True

        if preferences1:
            # Check constraints for 'preferences'
            preferences_list = preferences1.split(',')
            if len(preferences_list) > 5:
                messagebox.showwarning("Invalid Preferences", "Maximum of only 5 preferences are allowed")
                has_error = True

            for pref in preferences_list:
                if not re.match(r'^(MWF[0-9]{1,2}|TT[0-9]{1,2}(:[0-9]{2})?)$', pref):
                    messagebox.showwarning("Invalid Preference", "Invalid time format in preferences.")
                    has_error = True
                    break  # Exit the loop if an invalid preference is found

        # Check if the 'course_code' is present in the 'courses' table
        if not has_error:
            check_course_query = "SELECT course_code FROM courses WHERE course_code = %s"
            self.db_cursor.execute(check_course_query, (course_code1,))
            existing_course = self.db_cursor.fetchone()

            if not existing_course:
                messagebox.showwarning("Course Not Found", "The course code does not exist in the 'courses' table.")
                has_error = True

        # Check if the 'preferences' (if present) are in the 'timings' table
        if not has_error and preferences1:
            preferences_list = preferences1.split(',')
            for pref in preferences_list:
                check_time_query = "SELECT time_slot FROM timings WHERE time_slot = %s"
                self.db_cursor.execute(check_time_query, (pref,))
                existing_time = self.db_cursor.fetchone()

                if not existing_time:
                    messagebox.showwarning("Time Slot Not Found", f"The time slot '{pref}' does not exist in the 'timings' table.")
                    has_error = True
                    break  # Exit the loop if an invalid preference is found

        # If there's no error, insert data into the 'input2' table
        if not has_error:
            # Determine the 'Graduate' classification based on the course number
            graduate = "PG" if int(course_code1[2:]) > 600 else "UG"

            insert_query = "INSERT INTO input2 (course_code, enrollment, preferences, graduate) VALUES (%s, %s, %s, %s)"
            values = (course_code1, enrollment1, preferences1, graduate)
            try:
                self.db_cursor.execute(insert_query, values)
                self.db_connection.commit()
            except mc.IntegrityError as e:
                messagebox.showwarning("Duplicate Entry", "This course code already exists in the database.")

            # Clear the entry fields
            self.course_code_entry.delete(0, tk.END)
            self.enrollment_entry.delete(0, tk.END)
            self.preferences_entry.delete(0, tk.END)

    def display_tables(self):
        # Fetch and display data from 'rooms' table
        self.db_cursor.execute("SELECT room_number, capacity FROM rooms")
        room_data = self.db_cursor.fetchall()

        # Fetch and display data from 'courses' table
        self.db_cursor.execute("SELECT course_code FROM courses")
        course_data = self.db_cursor.fetchall()

        # Fetch and display data from 'timings' table
        self.db_cursor.execute("SELECT time_slot FROM timings")
        time_data = self.db_cursor.fetchall()

        if not room_data:
            messagebox.showwarning("Empty Room Table", "The 'rooms' table is empty. Please add rooms before displaying.")
        elif not course_data:
            messagebox.showwarning("Empty Course Table", "The 'courses' table is empty. Please add courses before displaying.")
        elif not time_data:
            messagebox.showwarning("Empty Timings Table", "The 'timings' table is empty. Please add timings before displaying.")
        else:
            # Display data from 'rooms' table
            self.rooms_label.config(text="Rooms and Capacities: \n" + "\n".join([f"Room:  {row[0]}, Capacity:  {row[1]}" for row in room_data]))

            # Display data from 'courses' table
            self.courses_label.config(text="Courses: \n" + "\n".join([f"Course:  {row[0]}" for row in course_data]))

            # Display data from 'timings' table
            self.timings_label.config(text="Timings: \n" + "\n".join([f"Time Slot: {row[0]}" for row in time_data]))

            # Create Room objects and add them to the list
            for row in room_data:
                room = Room(row[0], row[1])
                self.listRoom.append(room)

            # Create Course objects and add them to the list
            for row in course_data:
                course = Course(row[0])
                self.listCourse.append(course)

            # Create Time objects and add them to the list
            for row in time_data:
                time = Time(row[0])
                self.listTime.append(time)

            # Open the 'Course Scheduling 2' window
            self.open_input2_window()
    
    def display_input2(self):
        # Fetch and display data from 'input2' table
        self.db_cursor.execute("SELECT * FROM input2")
        input2_data = self.db_cursor.fetchall()

        # Display 'input2' data in the text widget
        self.input2_data_text.delete(1.0, tk.END)  # Clear previous data
        for row in input2_data:
            self.input2_data_text.insert(tk.END, f"Course Code: {row[0]}\nEnrollment: {row[1]}\nPreferences: {row[2]}\n\n")

    def create_time_table_window(self, time_table, room_data, time_data):
        time_table_window = tk.Toplevel(self.root)
        time_table_window.title("Time Table")

        # Create a Treeview widget for the timetable with 'Room' as the first column
        timetable_tree = ttk.Treeview(time_table_window, columns=['Room'] + [time.timing for time in time_data], show="headings")

        # Set column headings
        timetable_tree.heading('Room', text='Room')
        for time in time_data:
            timetable_tree.heading(time.timing, text=time.timing)
            timetable_tree.column(time.timing, width=100)  # Adjust column width as needed

        # Populate the timetable with course data
        for room in room_data:
            room_number = room.roomNo
            row_data = [room_number] + [time_table.get((time.timing, room_number), "") for time in time_data]
            timetable_tree.insert("", "end", values=row_data)

        # Pack the Treeview widget
        timetable_tree.pack()

    def create_exception_list_window(self, exception_list):
        exception_list_window = tk.Toplevel(self.root)
        exception_list_window.title("Exception List")

        # Create a list box to display the exception list
        listbox = tk.Listbox(exception_list_window, width=60, height=20)
        listbox.pack()

        # Insert exception list items
        for item in exception_list:
            listbox.insert(tk.END, item)

if __name__ == "__main__":
    root = tk.Tk()
    app = CourseSchedulingApp(root)
    root.mainloop()
