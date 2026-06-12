# AIWS_SPLIT_7


![AIWS_SPLIT_7](./AIWS_SPLIT_7.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AIWS_SPLIT_7** ist ein generischer Baustein, der einen einzelnen eingehenden AIWS-Adapter (unidirektional) auf sieben identische ausgehende AIWS-Adapter aufteilt. Er dient als Signalverteiler für automatisierungstechnische Anwendungen, bei denen ein Datenstrom oder eine Verbindung auf mehrere parallele Pfade kopiert werden muss.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine (der Funktionsblock besitzt keine Ereignis-Eingänge).

### **Ereignis-Ausgänge**
Keine (der Funktionsblock besitzt keine Ereignis-Ausgänge).

### **Daten-Eingänge**
Keine (der Funktionsblock besitzt keine direkten Daten-Eingänge; die Datenübertragung erfolgt ausschließlich über die Adapter-Schnittstellen).

### **Daten-Ausgänge**
Keine (der Funktionsblock besitzt keine direkten Daten-Ausgänge; die Datenübertragung erfolgt ausschließlich über die Adapter-Schnittstellen).

### **Adapter**
| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AIWS` | **IN** | Socket (Eingang) | Empfängt den zu verteilenden AIWS-Datenstrom. |
| `adapter::types::unidirectional::AIWS` | **OUT1** | Plug (Ausgang) | Erster identischer Ausgangskanal. |
| `adapter::types::unidirectional::AIWS` | **OUT2** | Plug (Ausgang) | Zweiter identischer Ausgangskanal. |
| `adapter::types::unidirectional::AIWS` | **OUT3** | Plug (Ausgang) | Dritter identischer Ausgangskanal. |
| `adapter::types::unidirectional::AIWS` | **OUT4** | Plug (Ausgang) | Vierter identischer Ausgangskanal. |
| `adapter::types::unidirectional::AIWS` | **OUT5** | Plug (Ausgang) | Fünfter identischer Ausgangskanal. |
| `adapter::types::unidirectional::AIWS` | **OUT6** | Plug (Ausgang) | Sechster identischer Ausgangskanal. |
| `adapter::types::unidirectional::AIWS` | **OUT7** | Plug (Ausgang) | Siebter identischer Ausgangskanal. |

## Funktionsweise
Der Funktionsblock empfängt über den Socket **IN** einen unidirektionalen Datenstrom vom Typ `AIWS`. Dieser Datenstrom wird intern ohne Änderung dupliziert und gleichzeitig an alle sieben Plugs **OUT1** bis **OUT7** weitergegeben. Jeder Ausgangskanal erhält somit exakt dieselben Daten wie der Eingang. Es findet weder eine Verzögerung noch eine Datenmanipulation statt.

## Technische Besonderheiten
- **Generischer Baustein** – Der FB ist als generische Komponente definiert (Attribut `GenericClassName` = `'GEN_AIWS_SPLIT'`), was eine typsichere Wiederverwendung in verschiedenen Kontexten ermöglicht.
- **Unidirektionale Adapter** – Alle verwendeten Adapter sind unidirektional, d.h. die Daten fließen nur vom Socket zu den Plugs.
- **Keine Ereignissteuerung** – Der FB besitzt keinen internen Zustandsautomaten und keine Ereignis-Ein-/Ausgänge; die Verteilung erfolgt rein datengetrieben.
- **Skalierbare Architektur** – Durch die modulare Adapter-Schnittstelle kann der Baustein in komplexen Hierarchien von Funktionsblöcken eingesetzt werden.

## Zustandsübersicht
Da der Funktionsblock über keinen Zustandsautomaten (ECC – Execution Control Chart) verfügt, existieren keine expliziten Zustände. Die Ausgangssignale sind stets direkt von den Eingangssignalen abhängig. Der FB arbeitet als reine Datenverteilung ohne Verzögerung oder Schalthandlungen.

## Anwendungsszenarien
- **Parallelverarbeitung** – Verteilung eines Messwertes oder Steuersignals auf mehrere unabhängige Regelungs- oder Überwachungspfade.
- **Signalüberwachung** – Gleiches Signal wird an verschiedene Diagnose- oder Logikblöcke geführt.
- **Redundanz** – Bereitstellung identischer Datenströme für unterschiedliche Empfänger (z. B. Bedienung, Visualisierung und Archivierung).
- **Testumgebungen** – Ein Testsignal kann gleichzeitig an mehrere Simulationsbausteine gesendet werden.

## Vergleich mit ähnlichen Bausteinen
- **AIWS_SPLIT_2, AIWS_SPLIT_4** – Bausteine mit gleicher Funktionalität, jedoch unterschiedlicher Anzahl an Ausgängen (2 bzw. 4). AIWS_SPLIT_7 bietet die maximale Anzahl an Ausgängen im Rahmen dieser Splitter-Familie.
- **Generische 1:N-Splitter** – In anderen IEC 61499-Bibliotheken existieren oft generische Splitter für Datentypen wie `ANY`. AIWS_SPLIT_7 ist speziell für den Adaptertyp `AIWS` ausgelegt und benötigt daher keine Typkonvertierung.

## Fazit
Der **AIWS_SPLIT_7** ist ein einfacher, aber leistungsfähiger Funktionsblock zur Vervielfachung eines unidirektionalen AIWS-Datenstroms auf sieben parallele Ausgänge. Seine generische Definition und die rein adapterbasierte Schnittstelle ermöglichen eine flexible Integration in IEC 61499-Anwendungen, insbesondere für Aufgaben der Signalverteilung und Parallelverarbeitung.