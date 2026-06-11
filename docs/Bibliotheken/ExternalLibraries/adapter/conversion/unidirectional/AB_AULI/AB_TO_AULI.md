# AB_TO_AULI


![AB_TO_AULI](./AB_TO_AULI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AB_TO_AULI** ist ein zusammengesetzter Baustein (Composite FB), der einen unidirektionalen Adapter vom Typ `AB` (BYTE) in einen unidirektionalen Adapter vom Typ `AULI` (ULINT) umwandelt. Er dient als Konverter zwischen unterschiedlichen Datentypen in der Adapterkommunikation nach IEC 61499-2. Der FB nutzt intern den standardisierten Konvertierungsbaustein `F_BYTE_TO_ULINT` aus der IEC 61131-Bibliothek.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **AB_IN.E1** – Ereigniseingang des AB-Adapter-Sockets. Wird durch das eingehende Adapterprotokoll ausgelöst und startet die Konvertierung.

### **Ereignis-Ausgänge**

- **AULI_OUT.E1** – Ereignisausgang des AULI-Adapter-Plugs. Signalisiert den Abschluss der Konvertierung an den nachgeschalteten Adapterpfad.

### **Daten-Eingänge**

- **AB_IN.D1** (Datentyp: BYTE) – Empfängt den zu konvertierenden Wert über den AB-Adapter.

### **Daten-Ausgänge**

- **AULI_OUT.D1** (Datentyp: ULINT) – Stellt den konvertierten ULINT-Wert über den AULI-Adapter bereit.

### **Adapter**

- **Socket „AB_IN“** – Typ: `adapter::types::unidirectional::AB`  
  Unidirektionaler Eingangsadapter für den Datentyp BYTE.

- **Plug „AULI_OUT“** – Typ: `adapter::types::unidirectional::AULI`  
  Unidirektionaler Ausgangsadapter für den Datentyp ULINT.

## Funktionsweise

Der FB wartet auf ein Ereignis am Eingangsadapter `AB_IN`. Sobald das Ereignis eintrifft, wird der an `AB_IN.D1` anliegende BYTE-Wert an den internen Konvertierungsbaustein `F_BYTE_TO_ULINT` weitergeleitet und dort in einen ULINT-Wert umgewandelt. Nach Abschluss der Konvertierung wird der resultierende Wert an `AULI_OUT.D1` ausgegeben und das Abschlussereignis an `AULI_OUT.E1` gesendet. Die gesamte Verarbeitung erfolgt ereignisgesteuert und ohne Zustandsautomaten.

## Technische Besonderheiten

- Der Baustein implementiert keine eigenen Zustände oder Algorithmen – er ist eine reine Verschaltung eines Standard-Konvertierungs-FBs.
- Die Konvertierung erfolgt nach den Regeln der IEC 61131-3: Der BYTE-Wert wird als 8‑Bit-Darstellung eines ULINT interpretiert und in eine vorzeichenlose 64‑Bit-Ganzzahl umgewandelt.
- Die Adapter basieren auf einem unidirektionalen Kommunikationsmuster, d. h. Daten und Ereignisse fließen nur in eine Richtung (vom Socket zum Plug).
- Der FB ist nicht zustandsbehaftet; jede Anforderung wird unabhängig verarbeitet.

## Zustandsübersicht

Der Baustein besitzt keinen eigenen Zustandsautomaten. Die Abarbeitung folgt einem einfachen ereignisgesteuerten Ablauf:

1. Warten auf Eingangsereignis (`AB_IN.E1`).
2. Konvertierung des Datenwerts.
3. Ausgabe des Ergebnisses und Auslösen des Ausgangsereignisses (`AULI_OUT.E1`).

## Anwendungsszenarien

- **Anbindung von BYTE-basierten Sensoren** an eine Steuerung, die ULINT als einheitlichen Datentyp für längere Messwerte verwendet.
- **Datenformatwandlung** inAdapterketten, wenn ein Protokoll auf BYTE-Ebene kommuniziert, aber die Anwendung einen ULINT-Wert erwartet.
- **Test- und Debugging-Aufbauten**, bei denen ein BYTE-Testadapter in eine ULINT-Schnittstelle umgesetzt werden soll.

## Vergleich mit ähnlichen Bausteinen

- **Direkte Konvertierung ohne Adapter** (z. B. `F_BYTE_TO_ULINT`): Diese Bausteine arbeiten auf Datenebene, nicht auf Adapterebene. Der `AB_TO_AULI` kapselt die Konvertierung inklusive der Adapterschnittstellen.
- **Adapter-Konverter für andere Datentypen** (z. B. `AB_TO_AUDINT`): Diese sind strukturell ähnlich, unterscheiden sich jedoch im Ziel-Datentyp und gegebenenfalls in der verwendeten Konvertierungsfunktion.
- **Bidirektionale Adapter-Konverter**: Falls erforderlich, müssten zwei unidirektionale Konverter (z. B. `AB_TO_AULI` und `AULI_TO_AB`) kombiniert werden.

## Fazit

Der FB `AB_TO_AULI` bietet eine einfache, standardkonforme Möglichkeit, einen BYTE-Adapter in einen ULINT-Adapter umzuwandeln. Durch die Verwendung eines etablierten IEC 61131-Konvertierungsbausteins ist die Konvertierung zuverlässig und leicht nachvollziehbar. Der Baustein ist ideal für Adapter-basierte Kommunikationsketten, die einen Datentypwechsel auf Adapterebene erfordern.