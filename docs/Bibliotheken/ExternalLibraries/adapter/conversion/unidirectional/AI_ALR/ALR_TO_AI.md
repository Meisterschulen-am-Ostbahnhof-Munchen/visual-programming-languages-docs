# ALR_TO_AI


![ALR_TO_AI](./ALR_TO_AI.svg)

* * * * * * * * * *

## Einleitung

Der **ALR_TO_AI** Funktionsblock ist ein Composite-Baustein, der einen Adapter des Typs ALR (LREAL-Daten) in einen Adapter des Typs AI (INT-Daten) umwandelt. Er wird eingesetzt, um Signale aus dem Bereich der landwirtschaftlichen Technik (z. B. Sensorwerte) auf ein standardisiertes integer-basiertes Adapterinterface zu bringen. Der Baustein kapselt die Konvertierung und Ereignisweiterleitung und erleichtert so die Integration in bestehende 4diac-Anwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine eigenständigen Ereignis-Eingänge auf der obersten Ebene. Die Ereignissteuerung erfolgt über den angeschlossenen Socket `ALR_IN`:

| Eingang | Typ | Beschreibung |
|---------|-----|--------------|
| `ALR_IN` | ALR (Socket) | Adapter, der über sein Ereignis (`E1`) die Konvertierung anstößt |

### **Ereignis-Ausgänge**

Der FB besitzt keine eigenständigen Ereignis-Ausgänge auf der obersten Ebene. Die Ereignisrückmeldung erfolgt über den angeschlossenen Plug `AI_OUT`:

| Ausgang | Typ | Beschreibung |
|---------|-----|--------------|
| `AI_OUT` | AI (Plug) | Adapter, der das konvertierte Ereignis (`E1`) nach erfolgreicher Umwandlung ausgibt |

### **Daten-Eingänge**

Über den Socket `ALR_IN` wird das **Daten-Eingangssignal** bereitgestellt:

| Adapter-Eingang | Datentyp | Beschreibung |
|-----------------|----------|--------------|
| `ALR_IN.D1` | LREAL | Der umzuwandelnde Gleitkommawert |

### **Daten-Ausgänge**

Über den Plug `AI_OUT` wird das **Daten-Ausgangssignal** bereitgestellt:

| Adapter-Ausgang | Datentyp | Beschreibung |
|-----------------|----------|--------------|
| `AI_OUT.D1` | INT | Der konvertierte Integer-Wert |

### **Adapter**

Der FB besitzt zwei Adapter-Schnittstellen:

* **Socket (Eingang)**: `ALR_IN` – Adapter für unidirektionale LREAL-Daten (Typ `adapter::types::unidirectional::ALR`)
* **Plug (Ausgang)**: `AI_OUT` – Adapter für unidirektionale INT-Daten (Typ `adapter::types::unidirectional::AI`)

## Funktionsweise

Der **ALR_TO_AI** enthält einen internen Konvertierungsbaustein `F_LREAL_TO_INT` aus der IEC 61131-Bibliothek.

1. Wenn der Socket `ALR_IN` ein Ereignis an seinem Ausgang `E1` sendet, wird dieses an den Eingang `REQ` des internen Konverters weitergeleitet.
2. Der Konverter wandelt den anliegenden LREAL-Wert (`ALR_IN.D1`) in einen INT-Wert um und gibt das Ergebnis über seinen Ausgang `OUT` sowie ein Bestätigungsereignis `CNF` aus.
3. Das `CNF`-Ereignis wird an den Plug `AI_OUT.E1` weitergegeben, sodass der nachgeschaltete Baustein über die Datenverfügbarkeit informiert wird.
4. Parallel wird der konvertierte INT-Wert auf den Datenausgang `AI_OUT.D1` gelegt.

Der gesamte Ablauf erfolgt synchron in einem Schritt.

## Technische Besonderheiten

* Der FB ist ein **Composite-Baustein** – er besitzt keine eigene Zustandsmaschine (ECC), sondern realisiert die Logik über ein internes Subnetzwerk.
* Die Konvertierung folgt der IEC 61131-3-Funktion `LREAL_TO_INT`: Nachkommastellen werden abgeschnitten (Abschneiden gegen Null), Über- oder Unterläufe sind implementierungsabhängig.
* Der Baustein ist als unidirektionale Adapter-Kopplung ausgelegt – es werden keine Rückkanäle unterstützt.

## Zustandsübersicht

Als Composite-FB besitzt **ALR_TO_AI** kein eigenes Zustandsdiagramm. Der interne Konverter `F_LREAL_TO_INT` arbeitet ereignisgesteuert: Ein Ereignis am Eingang `REQ` löst die Konvertierung aus, der Ausgang `CNF` signalisiert das Ende der Operation. Der FB verhält sich wie ein Transparentbaustein für die Ereignis- und Datenweiterleitung.

## Anwendungsszenarien

* **Sensorwertaufbereitung**: Umwandlung eines LREAL-Signals (z. B. von einem analogen Sensoradapter) in ein INT-Signal, das von einer SPS oder einer Steuerung mit integer-basierten Adaptern weiterverarbeitet wird.
* **Adapterbrücke**: Verbindung von Adaptertypen unterschiedlicher physikalischer Einheiten, wenn nur der Datentyp, nicht die Skalierung geändert werden muss.
* **Schnittstellenanpassung**: Einsatz in landwirtschaftlichen Steuerungen (z. B. HR Agrartechnik – allgemein), wo LREAL-Werte aus Sensoren auf ein CAN-basiertes INT-Adapterinterface abgebildet werden.

## Vergleich mit ähnlichen Bausteinen

| FB | Funktion | Unterschied |
|----|----------|-------------|
| **ALR_TO_AI** | Konvertiert LREAL → INT über Adapter | Composite, keine eigene Zustandsmaschine; verwendet IEC 61131-Konverter |
| `F_LREAL_TO_INT` | Reine Datenkonvertierung ohne Adapter | Direkter FB, benötigt separate Adapter-Anbindung |
| `AI_TO_ALR` | Umgekehrte Richtung INT → LREAL | Anderer Datentyp und Konvertierungsrichtung |

Der **ALR_TO_AI** vereinfacht die Wiederverwendung durch Kapselung der Adapterlogik und der Konvertierung in einem Baustein.

## Fazit

Der **ALR_TO_AI** ist ein praktischer Composite-FB zur standardisierten Umwandlung von LREAL- auf INT-basierte Adapterschnittstellen. Er erlaubt eine saubere Trennung von Datenkonvertierung und Adapterlogik und erleichtert die Integration in größere Automatisierungsprojekte. Dank der klaren Ereignisweiterleitung und der Nutzung einer IEC 61131-Basisfunktion ist er zuverlässig und einfach handhabbar.