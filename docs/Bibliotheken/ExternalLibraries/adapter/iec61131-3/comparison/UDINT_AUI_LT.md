# UDINT_AUI_LT


![UDINT_AUI_LT](./UDINT_AUI_LT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **UDINT_AUI_LT** realisiert den Vergleich "less than". Er prüft, ob der Wert am Eingang **IN1** kleiner als der Wert am Adaptereingang **IN2** ist. Das Ergebnis (BOOL) wird über den Ausgangsadapter **OUT** bereitgestellt. Durch die Verwendung von IEC 61131-3‑Adaptern wird eine flexible und modulare Anbindung an die Umgebung ermöglicht.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| **REQ** | Event | Service Request – löst den Vergleich aus (verbunden mit IN1) |

### **Ereignis-Ausgänge**
*(keine direkten Ereignisausgänge; das Ergebnisereignis wird über den Adapter OUT bereitgestellt)*

### **Daten-Eingänge**

| Name | Datentyp | Kommentar |
|------|----------|-----------|
| **IN1** | ANY_ELEMENTARY | Erster Vergleichswert |

### **Daten-Ausgänge**
*(keine direkten Datenausgänge; der Ergebniswert wird über den Adapter OUT bereitgestellt)*

### **Adapter**

| Richtung | Name | Adaptertyp | Kommentar |
|----------|------|------------|-----------|
| Eingang (Socket) | **IN2** | `adapter::types::unidirectional::AUI` | Zweiter Vergleichswert (wird über das Ereignis E1 des Adapters getriggert) |
| Ausgang (Plug)   | **OUT** | `adapter::types::unidirectional::AX` | Ergebnis (TRUE wenn IN1 < IN2, sonst FALSE) – wird über Ereignis E1 und Daten D1 bereitgestellt |

## Funktionsweise
Der Baustein ist als internes Netzwerk aus dem Basisbaustein **F_LT** (Typ `iec61131::comparison::F_LT`) aufgebaut.  
- Ein Ereignis an **REQ** oder am Adaptereingang **IN2.E1** triggert den internen F_LT über dessen Ereigniseingang **REQ**.  
- Die Datenwerte **IN1** und **IN2.D1** werden an die entsprechenden Dateneingänge von F_LT weitergeleitet.  
- F_LT führt den Vergleich `IN1 < IN2` durch und gibt das Ergebnis (BOOL) an **OUT.D1** aus.  
- Nach erfolgreichem Vergleich wird das Ereignis **OUT.E1** aktiviert.

## Technische Besonderheiten
- Der Baustein nutzt die IEC 61131-3‑Adapter **AUI** (unidirektionaler Eingang) und **AX** (unidirektionaler Ausgang). Dadurch kann der FB leicht in vorhandene adapternetzbasierte Architekturen eingebunden werden.
- Der Datentyp **ANY_ELEMENTARY** erlaubt die Verarbeitung aller elementaren Typen (BOOL, INT, REAL, …) – der tatsächliche Typ wird zur Laufzeit festgelegt.
- Es erfolgt keine eigene Zustandsverwaltung; die Logik wird vollständig durch den internen **F_LT** abgebildet.

## Zustandsübersicht
Der Baustein besitzt keinen eigenen Zustandsautomaten. Die Abarbeitung erfolgt rein ereignisgesteuert:
- **Warten auf Ereignis**: Kein Vergleich aktiv.
- **Vergleich aktiv**: Nach Eintreffen von **REQ** oder **IN2.E1** wird der interne F_LT ausgeführt.
- **Ausgabe**: Nach Abschluss des Vergleichs wird **OUT.E1** ausgelöst und das Ergebnis an **OUT.D1** bereitgestellt.

## Anwendungsszenarien
- **Grenzwertüberwachung**: Prüfen, ob ein Messwert (z. B. Temperatur, Druck) unter einem Sollwert liegt.
- **Steuerungslogik**: Bedingungen wie “Wenn Sensorwert < Schwellwert, dann Aktor einschalten”.
- **Modulare Automatisierung**: Einbinden in bestehende Adapter‑Strukturen ohne zusätzliche Konvertierungsbausteine.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Vergleichstyp | Besonderheit |
|----------|---------------|--------------|
| **F_LT** | less than | Direkte Ein‑/Ausgänge, kein Adapter |
| **UDINT_AUI_LT** | less than | Adapter für zweiten Eingang und Ausgang, modulare Kopplung |
| **F_LE** | less or equal | Vergleich ≤ |

Der vorliegende Baustein unterscheidet sich von **F_LT** durch die ausschließliche Verwendung von IEC‑Adaptern, was die Integration in adapterbasierte Komponenten (z. B. Dienste) erleichtert.

## Fazit
**UDINT_AUI_LT** stellt eine kompakte und flexible Lösung für den “kleiner als”‑Vergleich in IEC 61131-3‑Systemen dar. Die Adapter‑Schnittstellen ermöglichen eine saubere Trennung von Ereignis‑ und Datenflüssen und erlauben eine einfache Einbindung in komplexe Automatisierungsnetzwerke. Durch die Unterstützung elementarer Datentypen ist der Baustein vielseitig einsetzbar.