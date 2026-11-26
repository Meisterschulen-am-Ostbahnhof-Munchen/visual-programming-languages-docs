# ETP-Empfang in LOGIBUS

!!! warning "Stand: noch nicht gepusht, nicht getestet"
    Dieser Stand ist in der Firmware committet (LOGIBUS `24534469` „ETP-Empfang mit PSRAM-Puffer aktivieren“, forte `8d02d14f7` „AlPgnRxNew_TP: ETP-Empfang bis 65535 Byte“), aber **noch nicht gepusht und nicht auf Hardware getestet**. Die Angaben stammen von der Firmware-Entwicklung, ich habe die Commits nicht selbst geprüft. Hardware-Ergebnisse gibt es noch keine, getestet wird mit den ETP-Übungen im Trainingsprojekt.

Das Extended Transport Protocol (ETP) überträgt Nachrichten mit mehr als 1785 Byte. LOGIBUS kann ETP senden und, mit diesem Stand, auch empfangen.

## Was sich ändert

- **Bisher:** LOGIBUS konnte keine ETP empfangen. Der Standard-TP-Filter des CCI-Treibers verwarf jede ETP, und `iso_BaseInit` bekam keinen Speicher für ETP. Senden per ETP ging schon.
- **Neu:** LOGIBUS setzt einen eigenen TP-Filter (`iso_CoreInit`, `CoreTask.cpp`). Er nimmt TP und ETP bis `LOGIBUS_ETP_IN_SIZE_MAX` = 128 KiB an (`IsoConf.h`). Größere ETPs bricht der Stack mit „System resources“ ab.
- **Empfangspuffer:** Er kommt aus dem PSRAM (ETP-Memory-Callback in `BaseTask.cpp`, `heap_caps_malloc` mit `MALLOC_CAP_SPIRAM`). Der Stack gibt ihn nach der Verteilung der Daten frei, auch nach einem Abbruch.
- **Konfiguration:** Der als veraltet markierte Weg über `ISO_ETP_IN` wird nicht genutzt. Ab Treiber V12 sind eigener Filter plus Callback der vorgesehene Weg.

## In FORTE

- [`AlPgnRxNew_TP`](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/de/latest/Bibliotheken/ExternalLibraries/isobus/pgn/rx/AlPgnRxNew_TP/) übernimmt bis 65535 Byte (vorher 1785), `u16DaSize` gilt von 0 bis 65535. `OVERFLOW` zeigt an, dass `Data` zu klein war.
- [`AlPgnTxNew_TP`](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/de/latest/Bibliotheken/ExternalLibraries/isobus/pgn/tx/AlPgnTxNew_TP/) sendet bei `u16DaSize` über 1785 automatisch per ETP, bis 65535 Byte.
- [`DlPgnSend`](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/4diac-library-reference-docs/de/latest/Bibliotheken/ExternalLibraries/isobus/pgn/tx/DlPgnSend/) bleibt bei 1785 Byte.

## Einschränkungen

- ETP gibt es nur adressiert (destination specific), eine Rundsendung ist nicht möglich.
- PGNs von `0x1F000` bis `0x1FFFF` mit mehr als 8 Byte gehen als [NMEA Fast Packet](https://meisterschulen-am-ostbahnhof-munchen-docs.readthedocs.io/projects/isobus-other-docs/de/latest/NMEA2000-Fast-Packet/) (höchstens 223 Byte), nicht als ETP. Für ETP eignen sich Proprietary A2 (`0x1EF00`) oder Proprietary A (`0xEF00`).
