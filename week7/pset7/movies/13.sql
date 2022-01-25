-- Names of all actors who starred in a movie with Kevin Bacon

SELECT DISTINCT people.name FROM people
    JOIN stars ON stars.person_id = people.id
    JOIN movies ON movies.id = stars.movie_id
WHERE people.id
IN (
    SELECT stars.person_id FROM stars
    WHERE stars.movie_id
    IN (
        SELECT stars.movie_id FROM stars
        WHERE stars.person_id
        IN (
            SELECT people.id FROM people
            WHERE people.name = "Kevin Bacon" AND people.birth = 1958
        )
    )
);

/* sqlite>
name
Tippi Hedren
Orson Bean
Clint Eastwood
Frank Langella
Maximilian Schell
Jack Nicholson
Jeff Bridges
Robert De Niro
James Caan
Bob Balaban
John Lithgow
Kevin Costner
Bob Hoskins
Lindsay Crouse
Steve Guttenberg
Barbara Barrie
Daniel Stern
Meryl Streep
Diane Lane
Matt Dillon
James Doohan
Morgan Freeman
Rudy Ramos
Peter Gallagher
Fred Ward
Tommy Citera
Jennifer Jason Leigh
Elizabeth McGovern
Sean Penn
Mickey Rourke
Kevin Bacon
Mark Keyloun
Dianne Wiest
Demi Moore
Pete Seeger
Tom Cruise
Tess Harper
Karen Young
Maria Tucci
David Strathairn
Didi Velez
Tom Atkins
Kelly Preston
David Alan Grier
Bill Paxton
Nicolas Cage
Jami Gertz
Colin Firth
Tom Hanks
Kiefer Sutherland
Lori Singer
Elisabeth Shue
John Malkovich
Emily Longstreth
Bruce Payne
Richard Blade
Sean Astin
Josh Brolin
David Hayman
Linda Fiorentino
Mary Stuart Masterson
Christian Slater
Olympia Dukakis
Kyra Sedgwick
Elizabeth Perkins
Robert Patrick
Tim Robbins
Paul Rodriguez
Elya Baskin
Joe Mantegna
Gary Oldman
Jason Patric
John Goodman
Michael Beach
Alec Baldwin
Jonathan Ward
K.C. Martel
Andy Garcia
Sam Rockwell
Julia Roberts
James Ray
J.T. Walsh
Brad Pitt
Sarah Michelle Gellar
Finn Carter
Bridget Fonda
Campbell Scott
William Baldwin
Kristin Dattilo
Marcia Gay Harden
Winston Ntshona
Michael Gross
Anthony LaPaglia
Nathan Lane
Mary-Louise Parker
Embeth Davidtz
Brendan Fraser
Gary Sinise
Kathryn Erbe
Illeana Douglas
Jennifer Aniston
Ryan Reynolds
Charles Gitonga Maina
Yolanda Vazquez
Brad Renfro
Renée Zellweger
Joseph Mazzello
Andreas Michera
Denise Richards
Jim Cummings
Minnie Driver
Liv Tyler
Ray Stevenson
Charlize Theron
Luke Wilson
Neve Campbell
Ben Affleck
Courtney Love
Stuart Townsend
Yasiin Bey
Djimon Hounsou
Evan Rachel Wood
Marian Seldes
Jay Mohr
Calista Flockhart
Kim Dickens
Michael Harkins
Radha Mitchell
Frankie Muniz
Marin Hinkle
Zachary David Cope
Zooey Deschanel
Emmy Rossum
Mark Rendall
Alison Lohman
Michael Sheen
Shea Whigham
John Calley
James McAvoy
Garrett Hedlund
Rob Corddry
Logan Lerman
Ellen Page
Dominic Scott Kay
Jeffrey Baxter
Michael Cera
Michael Fassbender
Rainn Wilson
Amanda Seyfried
Miles Heizer
Christophe Beck
Jennifer Lawrence
Judd Apatow
Johnny A.
Russell Ali
Bill Gerber
Karen Anderson
Brittany Flickinger
Markus Waldow
Jirantanin Pitakporntrakul
Danny Abelson
Henry Beard
Lucy Fry
Joanna Angel
David Mazouz
Jill Anenberg
Carmine Appice
Joel Cox
Michael Bacon
N. Paul Stookey
Hays Wellford
James Freedson-Jackson
Air Supply
Avery Tiiu Essex
Colin Blumenau
Margie Adam
Melanie DeMore