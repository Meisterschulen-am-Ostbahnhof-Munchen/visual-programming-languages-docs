# ATimeOut

![ATimeOut](https://user-images.githubusercontent.com/116869307/214142228-09857ba5-6164-4597-bb66-8a99e74f4d14.png)

* * * * * * * * * *  

## Einleitung  
Der **ATimeOut**-Adapter ist eine standardisierte Schnittstelle (AdapterType) gemäß IEC 61499 zur Implementierung von Timeout-Services. Er definiert die Kommunikation zwischen einem Dienstnutzer (PLUG) und einem Zeitdienst-Anbieter (SOCKET). Im Gegensatz zum `ARTimeOut` ist dieser Adapter für einfache, nicht-nachtriggerbare Timeouts vorgesehen.

## Struktur des ATimeOut-Adapters  
Der ATimeOut-Adapter definiert eine klare Trennung der Zuständigkeiten zwischen der Steuerlogik (Plug) und dem Zeitgeber (Socket).

### Schnittstelle (Interface)  
Die Schnittstelle ist aus der Perspektive des **Plugs** definiert:

- **Eingangsereignisse (Event Inputs - vom Socket empfangen)**:  
  - **TimeOut**: Signalisiert, dass die vorgegebene Zeit abgelaufen ist.

- **Ausgangsereignisse (Event Outputs - an den Socket gesendet)**:  
  - **START**: Initiiert den Timeout-Vorgang. Dieses Ereignis ist mit der Variablen **DT** verknüpft.
  - **STOP**: Bricht einen laufenden Timeout-Vorgang ab.

- **Ausgangsvariablen (Output Variables - an den Socket gesendet)**:  
  - **DT (Duration Time)**: Definiert die Zeitdauer für den Timeout (Datentyp: TIME).

## Verhalten und Service-Sequenzen
Der Adapter unterstützt zwei grundlegende Abläufe:

1. **Timeout-Ablauf**:
   - Der Plug sendet `START` mit einem Wert für `DT`.
   - Der Socket verarbeitet die Zeit und sendet nach Ablauf `TimeOut` zurück.
2. **Vorzeitiger Abbruch**:
   - Der Plug sendet `START`.
   - Bevor die Zeit abläuft, sendet der Plug `STOP`. Der Socket bricht die Zeitmessung ab; es erfolgt kein `TimeOut`-Ereignis.

## Technische Besonderheiten
- **Nicht nachtriggerbar**: Ein erneutes `START` während eines laufenden Timeouts wird bei der Standard-Implementierung (`E_TimeOut`) ignoriert.
- **Adapter-Konzept**: Ermöglicht eine saubere Kapselung der Zeitlogik und vereinfacht das Baustein-Netzwerk durch Reduzierung der Verbindungslinien.

## Anwendungsbeispiele
- **Überwachung von Antwortzeiten**: Warten auf eine Bestätigung (z.B. von einem Kommunikationspartner) innerhalb eines festen Zeitfensters.
- **Prozessüberwachung**: Sicherstellen, dass ein mechanischer Vorgang innerhalb der erwarteten Zeit abgeschlossen wird.

## Vergleich mit ARTimeOut
| Feature        | ATimeOut (dieser) | ARTimeOut |
|----------------|-------------------|-----------|
| Typ            | Adapter           | Adapter   |
| Nachtriggerbar | Nein              | Ja        |
| Ereignis START | Startet Timer     | Startet/Resetet Timer |

## Fazit
Der ATimeOut-Adapter stellt eine robuste und einfache Schnittstelle für zeitkritische Überwachungsaufgaben in verteilten Steuerungssystemen dar. Er ist die Basis für den Funktionsbaustein `E_TimeOut`.
