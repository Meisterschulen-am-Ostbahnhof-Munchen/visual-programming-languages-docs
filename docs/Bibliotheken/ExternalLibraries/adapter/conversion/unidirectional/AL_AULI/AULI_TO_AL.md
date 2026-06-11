# AULI_TO_AL


![AULI_TO_AL](./AULI_TO_AL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AULI_TO_AL` ist ein Composite‑FB zur Umwandlung eines AULI‑Adapters (Datentyp ULINT) in einen AL‑Adapter (Datentyp LWORD). Er nutzt intern die IEC‑61131‑Konvertierungsfunktion `F_ULINT_TO_LWORD` und ist für den Einsatz in unidirektionalen Adapter‑Strukturen vorgesehen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Bezeichnung   | Beschreibung                                         |
|---------------|------------------------------------------------------|
| AULI_IN.E1    | Ereignisseingang über den Socket AULI_IN. Startet die Konvertierung. |

### **Ereignis-Ausgänge**

| Bezeichnung   | Beschreibung                                         |
|---------------|------------------------------------------------------|
| AL_OUT.E1     | Ereignisausgang über den Plug AL_OUT. Signalisiert den Abschluss der Konvertierung. |

### **Daten-Eingänge**

| Bezeichnung   | Datentyp | Beschreibung                                        |
|---------------|----------|-----------------------------------------------------|
| AULI_IN.D1    | ULINT    | Eingangswert, der in LWORD konvertiert werden soll. |

### **Daten-Ausgänge**

| Bezeichnung   | Datentyp | Beschreibung                                        |
|---------------|----------|-----------------------------------------------------|
| AL_OUT.D1     | LWORD    | Konvertierter Ausgangswert.                         |

### **Adapter**

| Bezeichnung | Typ       | Richtung | Beschreibung                              |
|-------------|-----------|----------|-------------------------------------------|
| AULI_IN     | AULI (ULINT) | Socket   | Unidirektionaler Eingangsadapter.         |
| AL_OUT      | AL (LWORD)   | Plug     | Unidirektionaler Ausgangsadapter.         |

## Funktionsweise

Der Baustein arbeitet als reine Weiterleitung: Ein eingehendes Ereignis an `AULI_IN.E1` triggert den internen Funktionsbaustein `F_ULINT_TO_LWORD`, welcher den aktuellen Wert von `AULI_IN.D1` ausliest und in einen LWORD‑Wert umrechnet. Nach Abschluss der Konvertierung wird der Ergebniswert an `AL_OUT.D1` ausgegeben und gleichzeitig ein Fertig‑Ereignis an `AL_OUT.E1` gesendet. Die interne Logik beschränkt sich auf die Daten‑ und Ereignisverbindungen zwischen dem Socket und dem internen Konverter.

## Technische Besonderheiten

- **Composite‑Implementierung**: Der Baustein enthält keine eigene Ablauflogik (ECC), sondern besteht ausschließlich aus einem verknüpften Funktionsbaustein der IEC‑61131‑Bibliothek.
- **Adapter‑Architektur**: Sowohl Eingang als auch Ausgang sind als unidirektionale Adapter (Socket/Plug) ausgelegt, was eine lose Kopplung und einfache Wiederverwendung in verschiedenen Applikationen ermöglicht.
- **Typumwandlung**: Die Konvertierung von ULINT (vorzeichenloser 64‑Bit‑Integer) nach LWORD (64‑Bit‑Bitfeld) erfolgt nach IEC‑61131‑Norm.

## Zustandsübersicht

Der Baustein besitzt keine eigene Zustandsmaschine. Die gesamte Funktionalität wird durch den internen FB `F_ULINT_TO_LWORD` realisiert, der als zustandslose Funktion arbeitet. Die Ereignissteuerung erfolgt ausschließlich über die in der Netzliste definierten Verbindungen.

## Anwendungsszenarien

- Integration von Sensorsystemen, die ULINT‑Daten über einen AULI‑Adapter liefern, in Steuerungen, die LWORD‑Daten über einen AL‑Adapter erwarten.
- Datentyp‑Migration oder Protokollanpassung in bestehenden Automatisierungslösungen.
- Einheitliche Adapterschnittstellen für Bibliotheken, die unterschiedliche physikalische Größen oder Adressräume abbilden.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu generischen Konverter‑Bausteinen (z. B. `ULINT_TO_LWORD`) ist `AULI_TO_AL` speziell auf den Adapter‑basierten Datenaustausch zugeschnitten. Ähnliche Adapter‑Konverter existieren für andere Datentypen (z. B. `BOOL_TO_BYTE`, `INT_TO_DINT`), unterscheiden sich jedoch in den verwendeten Adapter‑Typen und der internen Konvertierungsfunktion. Der vorliegende Baustein ergänzt die Bibliothek um eine saubere, typisierte Schnittstelle für ULINT↔LWORD.

## Fazit

`AULI_TO_AL` ist ein einfacher, aber zuverlässiger Composite‑FB zur Konvertierung zwischen AULI‑ und AL‑Adaptern. Durch die direkte Nutzung der standardisierten IEC‑61131‑Funktion wird eine hohe Kompatibilität und Korrektheit der Umwandlung sichergestellt. Die Adapter‑Schnittstellen ermöglichen eine modulare Einbindung in komplexe Automatisierungssysteme.