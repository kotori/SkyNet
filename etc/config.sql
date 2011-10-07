
DROP TABLE config;

CREATE TABLE config (
	id integer primary key,
	title text,
	x integer,
	y integer,
	full integer
);

INSERT INTO config VALUES(0, "SkyNet 800x600 Windowed", 800, 600, 0);
INSERT INTO config VALUES(1, "SkyNet 800x600 Fullscreen", 800, 600, 1);
INSERT INTO config VALUES(2, "SkyNet 1024x768 Windowed", 1024, 768, 0);
INSERT INTO config VALUES(3, "SkyNet 1024x768 Fullscreen", 1024, 768, 1);

