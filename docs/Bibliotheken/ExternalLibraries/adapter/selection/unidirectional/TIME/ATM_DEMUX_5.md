# ATM_DEMUX_5

  


![ATM_DEMUX_5](./ATM_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung

Der **ATM_DEMUX_5** ist ein generischer Demultiplexer-Baustein für fünf Ausgangskanäle. Er leitet die über einen unidirektionalen ATM‑Adapter empfangenen Daten an einen der fünf Ausgänge weiter, der durch einen Index **K** ausgewählt wird. Der Baustein realisiert damit eine 1‑zu‑N‑Verteilung (N=5) auf der Basis des ATM‑Adaptertyps.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
| :------- | :----------- |
| `REQ`    | Setzt den Index **K** und löst die Weiterleitung aus. Der Wert des Index wird zum Zeitpunkt des Ereignisses übernommen. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
| :------- | :----------- |
| `CNF`    | Bestätigt die erfolgreiche Weiterleitung an den gewählten Ausgang. |

### **Daten-Eingänge**

| Datum | Typ  | Beschreibung |
| :---- | :--- | :----------- |
| `K`   | UINT | Index des Zielausgangs (Wertebereich 1…5). |

### **Daten-Ausgänge**

Keine eigenen Daten-Ausgänge; die Datenweitergabe erfolgt über die Adapter-Ausgänge.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
| :------- | :--- | :--- | :----------- |
| Socket (Eingang) | `IN` | `adapter::types::unidirectional::ATM` | Empfängt die zu verteilenden Daten. |
| Plug (Ausgang 1) | `OUT1` | `adapter::types::unidirectional::ATM` | Erster Ausgangskanal. |
| Plug (Ausgang 2) | `OUT2` | `adapter::types::unidirectional::ATM` | Zweiter Ausgangskanal. |
| Plug (Ausgang 3) | `OUT3` | `adapter::types::unidirectional::ATM` | Dritter Ausgangskanal. |
| Plug (Ausgang 4) | `OUT4` | `adapter::types::unidirectional::ATM` | Vierter Ausgangskanal. |
| Plug (Ausgang 5) | `OUT5` | `adapter::types::unidirectional::ATM` | Fünfter Ausgangskanal. |

## Funktionsweise

1. Der Baustein wartet auf ein `REQ`‑Ereignis.  
2. Zum Zeitpunkt des Ereignisses wird der aktuelle Wert von **K** ausgelesen.  
3. Die Daten, die am Adapter `IN` anliegen, werden an den durch **K** bestimmten Ausgangsadapter (`OUT1` … `OUT5`) weitergegeben.  
4. Nach erfolgreicher Weiterleitung wird das Ereignis `CNF` ausgelöst.  

Gültige Werte für **K** sind 1 bis 5. Bei Werten außerhalb dieses Bereichs oder bei nicht definierten Indizes (z. B. 0) kann das Verhalten undefiniert sein – der Baustein führt in diesem Fall keine Aktion aus oder sendet kein `CNF`. Die maximale Anzahl von Ausgängen ist auf fünf festgelegt.

## Technische Besonderheiten

- **Generischer Aufbau**  
  Der Baustein ist als generischer Demultiplexer (`GEN_ATM_DEMUX`) deklariert. Das ermöglicht eine einfache Anpassung der Kanalanzahl oder des verwendeten Adaptertyps durch Neuinstantiierung mit unterschiedlichen Parametern.

- **Unidirektionale ATM‑Adapter**  
  Sowohl der Eingangs‑ als auch die Ausgangsadapter sind vom Typ `adapter::types::unidirectional::ATM`. Die Kommunikation erfolgt in einer Richtung (vom Eingang zu einem Ausgang), was für typische Verteileraufgaben ausreichend ist.

- **Index als UINT**  
  Der Index **K** ist als vorzeichenloser 16‑Bit‑Wert definiert, sodass numerisch 65536 mögliche Werte existieren, aber nur die ersten fünf (1…5) einem Ausgang zugeordnet sind. Dies erlaubt eine einfache Erweiterung, falls die Kanalanzahl später erhöht wird.

## Zustandsübersicht

Der Baustein besitzt keine explizite Zustandsmaschine. Das Verhalten ist rein ereignisgesteuert:

- **Ruhezustand**: Warten auf `REQ`.  
- **Verarbeitungszustand**: Bei Eintreffen von `REQ` wird der Index ausgewertet und die Weiterleitung durchgeführt. Anschließend wird sofort `CNF` gesendet. Der Baustein kehrt in den Ruhezustand zurück.

Es gibt keine dauerhaften Speicher oder internen Zustände.

## Anwendungsszenarien

- **Verteilen von ATM‑Datenströmen** in industriellen Kommunikationsnetzen, bei denen ein Datenkanal auf bis zu fünf Zielgeräte aufgeteilt werden muss.  
- **Routing in Automatisierungssystemen** – beispielsweise zur Ansteuerung mehrerer gleichartiger Aktoren über einen gemeinsamen Steuerkanal.  
- **Prüfstands‑ und Testumgebungen**, in denen ein Signal nacheinander an verschiedene Messpunkte gelegt werden soll.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion |
| :------- | :------- |
| `ATM_MUX` | Multiplexer: wählt einen von mehreren Eingängen und leitet ihn an einen Ausgang. |
| `ATM_DEMUX_5` | Demultiplexer: verteilt einen Eingang auf einen von fünf Ausgängen. |
| `ATM_DEMUX_X` | Variante mit variabler Kanalzahl (z. B. `ATM_DEMUX_8` für acht Ausgänge). |

Im Gegensatz zum Multiplexer realisiert der `ATM_DEMUX_5` die umgekehrte Richtung – von einem gemeinsamen Eingang zu mehreren Ausgängen. Er eignet sich daher für Stern‑ oder Bus‑Topologien mit einem Sender und mehreren Empfängern.

## Fazit

Der **ATM_DEMUX_5** ist ein einfacher, aber effektiver generischer Demultiplexer für unidirektionale ATM‑Adapter. Mit fünf Ausgangskanälen und ereignisgesteuerter Auswahl über einen Index **K** deckt er viele typische Verteilungsaufgaben in der Automatisierungstechnik ab. Durch seine generische Deklaration kann er leicht an andere Adaptertypen oder Kanalzahlen angepasst werden, ohne die grundlegende Funktionslogik zu ändern.