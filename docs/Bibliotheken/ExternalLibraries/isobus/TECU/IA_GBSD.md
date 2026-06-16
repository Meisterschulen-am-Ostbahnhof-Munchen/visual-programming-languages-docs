# IA_GBSD


![IA_GBSD](./IA_GBSD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **IA_GBSD** dient als Adapter-Wrapper für den ISOBUS-kompatiblen Baustein **I_GBSD** („Ground Based Speed and Distance“). Er kapselt die Initialisierung und Datenkommunikation eines bodenbasierten Geschwindigkeits- und Distanzsensors gemäß ISO 11783‑7 (PGN 65097) und stellt die Werte über unidirektionale Adapter-Schnittstellen bereit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar                       |
|------|-------|---------------------------------|
| INIT | EInit | Service Initialization          |

### **Ereignis-Ausgänge**

| Name  | Typ   | Kommentar                     |
|-------|-------|-------------------------------|
| INITO | EInit | Initialization Confirm        |

### **Daten-Eingänge**

| Name | Typ  | Kommentar                  |
|------|------|----------------------------|
| QI   | BOOL | Event Input Qualifier      |

### **Daten-Ausgänge**

| Name   | Typ    | Kommentar                     |
|--------|--------|-------------------------------|
| QO     | BOOL   | Event Output Qualifier        |
| STATUS | STRING | Statusinformation             |

### **Adapter**

| Name     | Typ                           | Kommentar                              |
|----------|-------------------------------|----------------------------------------|
| SPEED    | adapter::types::unidirectional::AUI  | Bodenbasierte Maschinengeschwindigkeit |
| DISTANCE | adapter::types::unidirectional::AUDI  | Bodenbasierte Maschinendistanz         |
| TIMEOUT  | adapter::types::unidirectional::AX   | Timeout-Status                         |

## Funktionsweise
Der FB ist als reiner Adapter-Wrapper realisiert:  
- Ein INIT-Ereignis am Eingang wird direkt an den internen Baustein **I_GBSD** weitergeleitet.  
- Der Daten-Eingang **QI** aktiviert bzw. deaktiviert die Verarbeitung.  
- Nach der Initialisierung wird das Ereignis **INITO** mit dem Qualifier **QO** und einem **STATUS** ausgegeben.  
- Die berechneten Grössen (Geschwindigkeit und Distanz) werden über die Adapter **SPEED** und **DISTANCE** ausgegeben; bei einer Zeitüberschreitung wird der **TIMEOUT**-Adapter aktiviert.  
- Alle Datenverbindungen werden innerhalb des FB-Netzwerks zwischen den Ein-/Ausgängen und dem internen Baustein hergestellt.

## Technische Besonderheiten
- **Adapter‑basierte Schnittstelle**: Die Ausgangsdaten werden nicht als feste Variablen, sondern über unidirektionale Adapter (AUI, AUDI, AX) bereitgestellt, was eine flexible Anbindung an andere Komponenten erlaubt.  
- **ISOBUS‑Konformität**: Der FB implementiert das PGN 65097 nach ISO 11783‑7 – Standard für bodenbasierte Geschwindigkeit und Distanz in der Landtechnik.  
- **Timeout‑Überwachung**: Der separate Timeout‑Adapter signalisiert, ob die Sensorwerte innerhalb einer erwarteten Zeitspanne aktualisiert wurden.  
- **Kompaktes Design**: Es gibt keinen eigenen Zustandsautomaten; alle Steuerlogik liegt im internen Baustein **I_GBSD**.

## Zustandsübersicht
Der FB selbst besitzt keinen expliziten Endlichen Automaten. Der interne Baustein durchläuft einen Initialisierungs‑Zustand (ausgelöst durch INIT) und einen Arbeitszustand, in dem kontinuierlich Geschwindigkeit, Distanz und Timeout‑Status aktualisiert werden.

## Anwendungsszenarien
- **ISOBUS‑Steuergeräte (TECU)**: Einbindung eines Radarsensors oder eines anderen bodenbasierten Geschwindigkeits‑/Distanzsensors in ein ISOBUS‑kompatibles System.  
- **Landwirtschaftliche Fahrzeuge**: Bereitstellung von Fahrgeschwindigkeit und zurückgelegter Strecke für nachgeschaltete Funktionen (z. B. dosierte Applikationen, Teilbreitenschaltung).  
- **Test‑ und Simulationsumgebungen**: Nutzung des Adapter‑Wrappers, um den realen Sensor durch eine simulierte Datenquelle zu ersetzen.

## Vergleich mit ähnlichen Bausteinen
- **IA_GBSD** vs. **I_GBSD**: I_GBSD ist der nativ programmierte ISOBUS‑Baustein, während IA_GBSD dessen Funktionalität ausschliesslich über Adapter zugänglich macht. Der Wrapper erleichtert die Verschaltung in grafischen Editoren und trennt die eigentliche Logik von der Schnittstellenanbindung.  
- **Alternative Adapter‑Wrapper**: Ähnliche Wrapper existieren für andere ISOBUS‑PGNs (z. B. für Navigationsdaten oder Arbeitshydraulik), die ebenfalls Adapter für ihre Ausgangswerte bereitstellen.

## Fazit
IA_GBSD ist ein effizienter Adapter‑Wrapper, der die bodenbasierte Geschwindigkeits‑ und Distanzmessung nach ISO 11783‑7 kapselt. Die Adapter‑Schnittstellen ermöglichen eine saubere modulare Integration in übergeordnete Steuerungslogiken, während die eigentliche ISOBUS‑Implementierung im Inneren erhalten bleibt. Dadurch wird der Baustein sowohl für direkte Anwendungen als auch für Simulations‑ und Testzwecke nutzbar.