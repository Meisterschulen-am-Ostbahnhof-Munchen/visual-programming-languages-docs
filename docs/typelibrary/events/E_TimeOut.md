# E_TimeOut

![E_TimeOut](https://user-images.githubusercontent.com/116869307/214142822-3b167702-112f-454a-a42f-62c5f7454561.png)

* * * * * * * * * *

## Einleitung
Der **E_TimeOut** ist ein standardkonformer Funktionsbaustein (IEC 61499-1) zur Implementierung von Timeout-Services. Version 1.0 bietet eine einfache, aber effektive Timeout-Funktionalität durch interne Nutzung eines E_DELAY-Bausteins. Der **E\_TimeOut** ist ein zusammengesetzter Funktionsblock. Innerhalb des Netzwerks eines zusammengesetzten Funktionsblocks wird jeder Adapter, der zu seiner Schnittstelle hinzugefügt wird, durch einen Adapterblock repräsentiert, der wie ein Funktionsblock aussieht. Die Schnittstellenelemente dieses Adapterblocks sind wie ein Funktionsblock verbunden.

## Schnittstellenstruktur

### **Adapter-Schnittstelle**
- `TimeOutSocket` (vom Typ ATimeOut):
  - Eingänge: `START`, `STOP`, `DT` (Delay Time)
  - Ausgang: `TimeOut`-Ereignis
  - **socket:** wird als Eingang eines Funktionsblocks hinzugefügt und innerhalb der Schnittstelle des Funktionsblocks dargestellt.  
  - **plug:** wird als Ausgang eines Funktionsblocks hinzugefügt und innerhalb der Schnittstelle des Funktionsblocks dargestellt.

![image](https://user-images.githubusercontent.com/113907483/227964793-560506b2-d55d-49af-91b8-ce9130149477.png)


### **Interne Komponenten**
- `DLY` (E_DELAY): Kernkomponente für die Zeitsteuerung

## Funktionsweise

1. **Timeout-Initialisierung**:
   - Bei `START`-Ereignis am Socket beginnt der Timer
   - Verwendet den konfigurierten `DT`-Wert

2. **Timeout-Operation**:
   - Timer läuft für die spezifizierte `DT`-Dauer
   - Keine Reset-Funktion (im Gegensatz zu E_RDELAY)

3. **Timeout-Abbruch**:
   - `STOP`-Ereignis bricht aktiven Timer ab

4. **Timeout-Auslösung**:
   - Nach Ablauf von `DT` wird `TimeOut`-Ereignis generiert
   - Signalisiert über den Adapter-Socket

## Technische Besonderheiten

✔ **Adapter-basierte** Schnittstelle  
✔ **Einfache Timeout-Logik**  
✔ **Deterministisches** Zeitverhalten  
✔ **Echtzeitfähige** Implementierung  

## Anwendungsszenarien

- **Netzwerkkommunikation**: Antwort-Timeout-Überwachung
- **Gerätesteuerung**: Watchdog-Funktionen
- **Prozessüberwachung**: Zeitbegrenzte Operationen
- **Sicherheitssysteme**: Notfall-Timeout

## Vergleich mit E_RDELAY

| Feature        | E_TimeOut | E_RDELAY |
|---------------|-----------|----------|
| Reset-Funktion | ❌        | ✔️       |
| Adaptertyp    | ATimeOut  | ARTimeOut |
| Komplexität   | Einfach   | Erweitert |

## Fazit

Der E_TimeOut-Baustein bietet eine robuste Grundimplementierung für Timeout-Anforderungen:

- Einfache und zuverlässige Zeitüberwachung
- Standardisierte Adapter-Schnittstelle
- Klare Funktionsweise ohne Reset-Komplexität

Durch die Verwendung des bewährten E_DELAY-Bausteins im Kern gewährleistet er präzise Zeitsteuerung für grundlegende Automatisierungsaufgaben. Die IEC 61499-Konformität ermöglicht einfache Integration in verteilte Steuerungssysteme.