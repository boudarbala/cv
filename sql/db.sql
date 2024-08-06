-- Create tables
CREATE TABLE IF NOT EXISTS personal_info (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    email TEXT NOT NULL,
    phone TEXT,
    address TEXT,
    summary TEXT
);

CREATE TABLE IF NOT EXISTS skills (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    personal_info_id INTEGER NOT NULL,
    skill TEXT NOT NULL,
    FOREIGN KEY (personal_info_id) REFERENCES personal_info(id)
);

CREATE TABLE IF NOT EXISTS experience (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    personal_info_id INTEGER NOT NULL,
    job_title TEXT NOT NULL,
    company TEXT NOT NULL,
    start_date TEXT NOT NULL,
    end_date TEXT,
    description TEXT,
    FOREIGN KEY (personal_info_id) REFERENCES personal_info(id)
);

CREATE TABLE IF NOT EXISTS education (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    personal_info_id INTEGER NOT NULL,
    institution TEXT NOT NULL,
    degree TEXT NOT NULL,
    start_date TEXT NOT NULL,
    end_date TEXT,
    description TEXT,
    FOREIGN KEY (personal_info_id) REFERENCES personal_info(id)
);

-- Insert sample data
INSERT INTO personal_info (name, email, phone, address, summary) 
VALUES ('John Doe', 'john.doe@example.com', '123-456-7890', '123 Main St, Anytown, USA', 'Experienced software developer with a strong background in web development.');

INSERT INTO skills (personal_info_id, skill) VALUES (1, 'C++');
INSERT INTO skills (personal_info_id, skill) VALUES (1, 'Java');
INSERT INTO skills (personal_info_id, skill) VALUES (1, 'Python');
INSERT INTO skills (personal_info_id, skill) VALUES (1, 'HTML/CSS');
INSERT INTO skills (personal_info_id, skill) VALUES (1, 'JavaScript');

INSERT INTO experience (personal_info_id, job_title, company, start_date, end_date, description) 
VALUES (1, 'Software Developer', 'Tech Solutions Inc.', '2019-06-01', '2023-08-01', 'Developed web applications using various technologies.');

INSERT INTO experience (personal_info_id, job_title, company, start_date, end_date, description) 
VALUES (1, 'Junior Developer', 'Web Innovators LLC', '2017-01-01', '2019-05-31', 'Assisted in the development and maintenance of web applications.');

INSERT INTO education (personal_info_id, institution, degree, start_date, end_date, description) 
VALUES (1, 'State University', 'Bachelor of Science in Computer Science', '2013-09-01', '2017-06-01', 'Completed coursework in computer science, focusing on software development.');

INSERT INTO education (personal_info_id, institution, degree, start_date, end_date, description) 
VALUES (1, 'Community College', 'Associate of Science in Information Technology', '2011-09-01', '2013-06-01', 'Studied fundamental concepts of information technology and computer science.');
