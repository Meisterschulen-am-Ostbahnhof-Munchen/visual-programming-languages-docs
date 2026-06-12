# AX_TO_AULI


![AX_TO_AULI](./AX_TO_AULI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_TO_AULI** ist ein Composite-Baustein zur Konvertierung eines BOOL‑Adapter-Signals (Typ `AX`) in ein ULINT‑Adapter-Signal (Typ `AULI`).  
Er kapselt die typsichere Umwandlung eines binären Werts in einen vorzeichenlosen 64‑Bit‑Integer und ermöglicht so die einfache Integration von BOOL‑Schnittstellen in ULINT‑basierte Steuerungslogiken.  
Der Baustein wird im Paket `adapter::conversion::unidirectional` bereitgestellt und basiert auf dem standardisierten Konvertierungsbaustein `F_BOOL_TO_ULINT` aus der IEC‑61131‑Bibliothek.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine eigenen Ereignis-Eingänge.  
Die Ereignissteuerung erfolgt über die angeschlossenen Adapter (siehe Abschnitt **Adapter**).

### **Ereignis-Ausgänge**

Keine eigenen Ereignis-Ausgänge.  
Die Ergebnisereignisse werden über den Ausgangsadapter bereitgestellt (siehe Abschnitt **Adapter**).

### **Daten-Eingänge**

Keine eigenen Daten-Eingänge.  
Die zu konvertierenden Daten werden über den Eingangsadapter empfangen (siehe Abschnitt **Adapter**).

### **Daten-Ausgänge**

Keine eigenen Daten-Ausgänge.  
Das konvertierte Ergebnis wird über den Ausgangsadapter bereitgestellt (siehe Abschnitt **Adapter**).

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket | `AX_IN` | `adapter::types::unidirectional::AX` | BOOL‑Adapter‑Eingang. Stellt über das Ereignis `E1` und das Datum `D1` (BOOL‑Wert) die Eingangsdaten bereit. |
| Plug | `AULI_OUT` | `adapter::types::unidirectional::AULI` | ULINT‑Adapter‑Ausgang. Gibt über das Ereignis `E1` und das Datum `D1` (ULINT‑Wert) das Konvertierungsergebnis aus. |

## Funktionsweise

Der Baustein enthält ein internes Netzwerk, das aus einer einzigen Instanz des Konvertierungsbausteins `F_BOOL_TO_ULINT` besteht.  
Die Verbindungen sind wie folgt:

1. **Ereignisführung**:  
   - Das Ereignis `AX_IN.E1` (vom Eingangsadapter) wird an den Ereigniseingang `Convert.REQ` geleitet und startet die Konvertierung.  
   - Nach Abschluss der Konvertierung wird das Ereignis `Convert.CNF` an den Ereignisausgang `AULI_OUT.E1` weitergegeben, um abschließend den Ausgangsadapter zu aktualisieren.

2. **Datenfluss**:  
   - Der boolesche Wert von `AX_IN.D1` wird auf den Dateneingang `Convert.IN` gespiegelt.  
   - Der konvertierte ULINT‑Wert von `Convert.OUT` wird auf `AULI_OUT.D1` übertragen.

Somit wird bei jeder steigenden Flanke des Eingangsereignisses der aktuelle BOOL‑Wert in einen ULINT‑Wert umgewandelt (BOOL → 0 → 0 ULINT, BOOL → 1 → 1 ULINT) und über den Ausgangsadapter bereitgestellt.

## Technische Besonderheiten

- **Lizenz**: Der Quellcode steht unter der *Eclipse Public License 2.0* (EPL‑2.0).  
- **Urheber**: Entwickelt von **Franz Höpfinger** für die **HR Agrartechnik GmbH** (Version 1.0, Stand 2026‑02‑17).  
- **Paketstruktur**: Der Baustein ist im Paket `adapter::conversion::unidirectional` organisiert.  
- **Abhängigkeiten**: Er importiert den Baustein `iec61131::conversion::F_BOOL_TO_ULINT`.  
- **Typsicherheit**: Durch die Verwendung von Adaptern wird eine strenge Typüberprüfung bereits zur Entwurfszeit gewährleistet.

## Zustandsübersicht

Der Composite‑Baustein besitzt keine eigene Zustandsmaschine.  
Die gesamte Ablaufsteuerung wird durch den internen Baustein `F_BOOL_TO_ULINT` realisiert, der einen einfachen ereignisgesteuerten Zustandsautomaten umsetzt:  
- Im Ruhezustand wartet er auf ein `REQ`-Ereignis.  
- Nach Eintreffen des Ereignisses wird die Konvertierung durchgeführt und unmittelbar der Ausgang mit `CNF` bestätigt.

## Anwendungsszenarien

- **Integration von Binärsensoren** in Steuerungen, die ULINT‑Werte erwarten (z. B. Zählerregister, Adressierungslogiken).  
- **Adapter‑Brückenbildung** in heterogenen Systemen, bei denen ein BOOL‑Adapter (z. B. von einem Schalter) an einen ULINT‑Adapter (z. B. einer Profil‑/Parametrierschnittstelle) angepasst werden muss.  
- **Typsichere Konvertierung** in Composite‑Bausteinen, um die Handhabung unterschiedlicher Datentypen in einer Applikation zu vereinheitlichen.

## Vergleich mit ähnlichen Bausteinen

- **F_BOOL_TO_ULINT**: Der zugrunde liegende Basisbaustein – er bietet die reine Konvertierung ohne Adapter‑Kapselung.  
- **AX_TO_UDINT**, **AX_TO_DINT**: Analog aufgebaute Composite‑Bausteine für andere Zieldatentypen (UDINT, DINT).  
- **Direkte Typumwandlung**: Im IEC‑61131‑Umfeld existieren zahlreiche Standard‑Konvertierungsbausteine; der vorliegende spezialisiert sich auf die Adapter‑Schnittstelle.

## Fazit

Der Baustein **AX_TO_AULI** ist eine kompakte, typsichere und leicht wiederverwendbare Lösung zur Umwandlung eines BOOL‑Adapters in einen ULINT‑Adapter.  
Er vereinfacht die hierarchische Strukturierung von Applikationen und ermöglicht eine klare Trennung zwischen Datenquellen und -senken. Dank der Lizenzierung unter EPL‑2.0 kann er frei in eigene Projekte integriert werden.