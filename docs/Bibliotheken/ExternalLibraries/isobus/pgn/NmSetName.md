# NmSetName

```{index} single: NmSetName
```

<img width="1021" height="248" alt="image" src="https://github.com/user-attachments/assets/313bb66b-066d-4f13-adfb-b0d058074d2d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `NmSetName` dient der Konvertierung einer strukturierten Namensfeld-Definition in ein kompaktes, 8-Byte langes ISO-NAME gemäß der Spezifikation ISO 11783-5 (Abschnitt 5.1.2). Dieser Baustein ist ein wesentlicher Bestandteil für die Geräteidentifikation und -adressierung in ISOBUS-Netzwerken (Landwirtschaftliche und Forstmaschinen). Er übernimmt die Bit-genaue Zuordnung der einzelnen Felder einer `NAMEFIELD_T`-Struktur in das entsprechende Byte-Array eines `CF_NAME_T`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Dieses Ereignis löst die Konvertierung aus. Bei seinem Eintreffen werden die anliegenden Daten am Eingang `psNameField` verarbeitet.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses Ereignis signalisiert den Abschluss der Verarbeitung. Es wird nach der erfolgreichen Umwandlung der Eingangsdaten generiert.

### **Daten-Eingänge**
*   **psNameField** (`isobus::pgn::NAMEFIELD_T`): Die Eingangsstruktur, die alle Einzelkomponenten eines ISOBUS-Namens (wie Herstellercode, Geräteklasse, Funktionsinstanz, etc.) in einem für den Programmierer gut handhabbaren Format enthält.

### **Daten-Ausgänge**
*   **(Unbenannt)** (`isobus::pgn::CF_NAME_T`): Der Ausgang liefert das resultierende 8-Byte große ISO-NAME-Array (`data[0]` bis `data[7]`), das direkt in ISOBUS-Nachrichten verwendet werden kann.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Baustein arbeitet als reiner Daten-Transformer. Bei Auslösung durch das `REQ`-Ereignis liest er die Werte aus der Eingangsstruktur `psNameField` und verteilt sie gemäß der ISO-Norm bitweise auf die acht Bytes des Ausgangs-Arrays. Die Logik besteht aus einer sequentiellen Abfolge von bitweisen Operationen (AND, OR, SHL) und Typkonvertierungen. Jede Zeile im ST-Code setzt bestimmte Bits in einem spezifischen Byte des `CF_NAME_T`-Ausgangs, während die restlichen Bits unverändert bleiben (durch die `AND`-Operationen maskiert). Nachdem alle Bytes gesetzt sind, wird das `CNF`-Ereignis ausgegeben.

## Technische Besonderheiten
*   **Bitweise Verarbeitung:** Die Kernfunktionalität basiert auf präzisen bitweisen Operationen, um die komplexe Struktur des ISO-NAME in ein kompaktes Byte-Array zu packen.
*   **Typensicherheit:** Es werden explizite Typkonvertierungen (z.B. `DWORD_TO_BYTE`, `WORD_TO_BYTE`) verwendet, um die korrekte Datenhandhabung sicherzustellen.
*   **Normkonformität:** Die Implementierung folgt strikt der Bit-Zuordnung, wie sie in ISO 11783-5 definiert ist.
*   **Zustandslos:** Der Block besitzt keinen internen Zustand zwischen zwei Aufrufen. Die Ausgabe hängt ausschließlich von den aktuellen Eingabedaten ab.

## Zustandsübersicht
Der Funktionsblock ist zustandslos. Sein Verhalten lässt sich als einfache, deterministische Funktion beschreiben:
1.  **Warten:** Block wartet auf das `REQ`-Ereignis.
2.  **Verarbeiten:** Bei `REQ` werden die Eingangsdaten verarbeitet und das Ausgangs-Array berechnet.
3.  **Bestätigen:** Unmittelbar nach der Berechnung wird das `CNF`-Ereignis ausgegeben.
Der Block kehrt danach direkt wieder in den Wartezustand (1) zurück.

## Anwendungsszenarien
*   **Initialisierung eines ISOBUS-Knotens:** Beim Start eines Steuergeräts (ECU) in einem ISOBUS-Netzwerk muss dessen eindeutiger NAME aus konfigurierbaren Parametern (z.B. aus einem NVRAM) zusammengesetzt und in die Kommunikationsstack eingetragen werden.
*   **Dynamische Gerätekonfiguration:** In Systemen, wo sich die Geräteeigenschaften (z.B. Funktionsinstanz) zur Laufzeit ändern können, wird dieser Block verwendet, um den neuen, gültigen NAME zu generieren.
*   **Test- und Simulationstools:** Zum Erzeugen von korrekten ISO-NAMEs für die Simulation verschiedener virtueller Geräte in einem ISOBUS-Netzwerk.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **Gegenstück `NmGetName`:** Während `NmSetName` eine strukturierte Beschreibung in ein Byte-Array packt, würde ein hypothetischer `NmGetName`-Block die umgekehrte Operation durchführen: Er extrahiert aus einem gegebenen ISO-NAME-Byte-Array die einzelnen Felder und stellt sie in einer `NAMEFIELD_T`-Struktur bereit. `NmSetName` ist somit der "Encoder", sein Pendant wäre der "Decoder".
*   **Generische Byte-Packer:** Im Gegensatz zu generischen Bausteinen, die beliebige Datenstrukturen serialisieren, ist `NmSetName` spezifisch auf die ISO 11783-NAME-Struktur optimiert und garantiert so Normkonformität ohne zusätzliche Konfiguration.




## 🛠️ Zugehörige Übungen

* [Uebung_121](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_121.md)

## Fazit
Der `NmSetName`-Funktionsblock ist ein spezialisierter, unverzichtbarer Baustein für die ISOBUS-Kommunikation. Er abstrahiert die komplexe, bitgenaue Zusammensetzung des ISO-NAME gemäß der Norm und bietet dem Anwender eine einfache, strukturierte Schnittstelle. Seine deterministische und zustandslose Funktionsweise macht ihn robust und einfach in Steuerungsabläufe zur Geräteinitialisierung und -konfiguration integrierbar.