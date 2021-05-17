# B2F5_Gloomi-10_Backend
Mocht er iets niet duidelijk zijn bekijk Film_werking.MP4 in de bestanden voor meer uitleg

App aanmaken in TTN:
1. ga naar https://console.thethingsnetwork.org/
2. Klik op application
3. add application
4. app id = gloomi
5. handler is ttn handler eu
6. derest kan je zelf invullen

7. In de app ga naar settings
8. acces keys
9. Maak een nieuwe acces key met alle permissie en geef deze een naam
10. Verander de app id en acc key variabele in hetpython programma

11. ga naar payload formats
12. decoder
13. Plak hier de code uit Ttn_decoder_payloadformat.txt

14. Ga naar devices
15. register device
16. device id = arduino
17. laat de dev eui en app key automatisch genereren
18. register

19. ga naar settings
20. activation method = abp
21. apply

22. ga naar overview en vervang de network sessionkey, app session key en het device addres in Arduino_ttn_implementation.ino met de hex waarde uit dit overview( laat de 0x bij devaddr staan)

23. Verbind alle sensoren met de arduino zoals op de foto's weergeven en import de libraries in de arduino editor

24. voer het database create script uit

25. verander de database connect string met je eigen in de frontend visual studio solution.

Alles is nu opgezet om alles te runnen moet het volgende gebeuren.
1. Upload de .ino code naar de arduino
2. Wacht tot deze verbonden is(kan best een half uur duren) door de kijken in de data tab van het device in ttn.
3. start het python programma en kijk of deze ook de data uit ttn ontvangt
4. start het monitor programma voeg de arduino toe met "arduino" als naam en bekijk de "real time gegevens" van de arduino

