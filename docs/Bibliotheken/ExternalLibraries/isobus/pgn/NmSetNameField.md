# NmSetNameField

```{index} single: NmSetNameField
```

<img width="1070" height="248" alt="image" src="https://github.com/user-attachments/assets/f7752178-ab95-47c7-9972-b0f2c8b49ec3" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `NmSetNameField` dient der Konvertierung eines ISO-NAME gemäß der Spezifikation ISO 11783-5 (Abschnitt 5.1.2) in eine strukturierte Darstellung. Ein ISO-NAME ist ein 8-Byte langer Bezeichner, der in landwirtschaftlichen und forstwirtschaftlichen Maschinen (ISOBUS) zur eindeutigen Identifikation von Steuergeräten (ECUs) verwendet wird. Dieser Baustein extrahiert die einzelnen Felder aus dem Byte-Array und füllt eine entsprechende Datenstruktur (`NAMEFIELD_T`). Dies erleichtert die weitere Verarbeitung und Auswertung der Geräteinformationen in einer IEC 61499-Applikation.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Startet die Verarbeitung. Bei Empfang dieses Ereignisses wird der an `au8IsoName` anliegende Wert verarbeitet.

### **Ereignis-Ausgänge**
*   **CNF**: Wird ausgelöst, sobald die Konvertierung abgeschlossen ist und die strukturierten Daten am Ausgang bereitstehen.

### **Daten-Eingänge**
*   **au8IsoName** (`isobus::pgn::CF_NAME_T`): Ein 8-Byte langes Array, das den rohen ISO-NAME gemäß ISO 11783-5 enthält.

### **Daten-Ausgänge**
*   **(kein expliziter Name)** (`isobus::pgn::NAMEFIELD_T`): Die Ausgabevariable enthält die strukturierte Aufschlüsselung des ISO-NAME. Der genaue Aufbau der `NAMEFIELD_T`-Struktur wird durch die verwendete `isobus::pgn`-Bibliothek definiert.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses verarbeitet der Baustein das anliegende Byte-Array `au8IsoName`. Die Implementierung in Structured Text (ST) extrahiert bit- und byteweise die einzelnen Komponenten des ISO-NAME und weist sie den entsprechenden Feldern der `NAMEFIELD_T`-Ausgabestruktur zu. Die Logik folgt exakt der Bit-Zuordnung, wie sie in ISO 11783-5, Abschnitt 5.1.2, definiert ist. Nach Abschluss der Berechnungen wird das `CNF`-Ereignis gesetzt, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
*   **Bitmanipulation:** Der Block verwendet logische UND-Operationen (`AND`), Schiebeoperationen (`SHL`, `SHR`) und Typkonvertierungen (`BYTE_TO_WORD`, `BYTE_TO_DWORD`), um die relevanten Bits aus dem Eingabe-Array zu isolieren.
*   **Bibliotheksabhängigkeit:** Der Block ist von den Datentypen `CF_NAME_T` und `NAMEFIELD_T` der `isobus::pgn`-Bibliothek abhängig. Die genaue Definition dieser Typen (z.B. die Feldnamen in `NAMEFIELD_T`) liegt außerhalb dieses Blocks.
*   **Deterministisch:** Die Operation ist rein datengetrieben und hat keinen internen Zustand. Bei gleicher Eingabe erzeugt sie stets die gleiche Ausgabe.

## Zustandsübersicht
Der Funktionsblock besitzt keinen persistenten internen Zustand. Er verhält sich wie eine reine Funktion:
1.  **Warte- bzw. Idle-Zustand:** Block wartet auf das `REQ`-Ereignis.
2.  **Verarbeitungszustand:** Bei `REQ` werden die Eingangsdaten verarbeitet und die Ausgangsstruktur berechnet. Dieser Zustand ist instantan (keine Verzögerung).
3.  **Ausgabe:** Unmittelbar nach der Berechnung wird das `CNF`-Ereignis ausgelöst und die berechnete `NAMEFIELD_T`-Struktur ausgegeben. Der Block kehrt danach in den Wartezustand zurück.

## Anwendungsszenarien
*   **ISOBUS-Geräteerkennung:** In einem ISOBUS-Netzwerkmanager, der eingehende NAME-Daten von angeschlossenen ECUs decodieren muss, um Gerätetyp, Hersteller und Instanz zu identifizieren.
*   **Diagnose und Protokollierung:** Zur übersichtlichen Darstellung und Protokollierung von Gerätenamen in menschenlesbarer, strukturierter Form anstelle des rohen 8-Byte-Wertes.
*   **Filterung und Adressierung:** Als Vorverarbeitungsschritt, um basierend auf spezifischen Feldern (wie Geräteklasse oder Herstellercode) Entscheidungen über die weitere Kommunikation zu treffen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **Gegenstück `NmGetIsoName`:** Ein hypothetischer komplementärer Baustein würde die umgekehrte Operation durchführen: Er nähme eine `NAMEFIELD_T`-Struktur als Eingabe und erzeugte daraus das entsprechende 8-Byte-`CF_NAME_T`-Array. `NmSetNameField` ist der Dekodierer, sein Gegenstück wäre der Kodierer.
*   **Generische Byte-Parser:** Im Gegensatz zu generischen Byte-zu-Struktur-Konvertern ist dieser Block spezifisch auf das ISO-NAME-Format zugeschnitten und enthält die exakte Bitlogik der Norm. Die Verwendung dieses spezialisierten Blocks reduziert Fehler und erhöht die Wartbarkeit im ISOBUS-Kontext.




## 🛠️ Zugehörige Übungen

* [Uebung_120](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_120.md)
* [Uebung_121](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_121.md)
* [Uebung_122](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_122.md)
* [Uebung_122b](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_122b.md)

## Fazit
Der `NmSetNameField`-Funktionsblock ist ein essenzielles Hilfsmittel für die Arbeit mit ISOBUS-Netzwerken in 4diac. Er abstrahiert die komplexe Bit-Manipulation, die zur Interpretation des ISO-NAME erforderlich ist, und stellt die Informationen in einer leicht verarbeitbaren strukturierten Form bereit. Seine Verwendung fördert korrekte, normkonforme Applikationen und verbessert die Lesbarkeit des Quellcodes erheblich.