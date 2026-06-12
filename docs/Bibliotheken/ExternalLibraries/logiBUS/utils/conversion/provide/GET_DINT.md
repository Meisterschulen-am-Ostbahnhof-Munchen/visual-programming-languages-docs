# GET_DINT


![GET_DINT](./GET_DINT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **GET_DINT** liest einen DINT-Wert aus einer InOut-Variable und stellt diesen als gepufferten Ausgangswert bereit. Die Variable wird dabei nicht verändert; der Baustein dient als reiner Lese- und Pufferbaustein.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ** – Normaler Ausführungsauftrag (aktiviert das Auslesen der InOut-Variable).

### **Ereignis-Ausgänge**
- **CNF** – Bestätigung der Ausführung (wird nach erfolgreicher Übernahme des Wertes gesendet).

### **Daten-Eingänge**
Es sind keine klassischen Daten-Eingänge vorhanden. Die Quelle des Wertes wird über die nachfolgend beschriebene InOut-Variable bereitgestellt.

### **Daten-Ausgänge**
- **OUT** (Typ: DINT, Initialwert: 0) – Gepufferter Ausgangswert, der den aktuellen Wert der InOut-Variable enthält.

### **Adapter**
Keine.

**Besonderheit:** Der Baustein verwendet eine **InOut-Variable** mit der Bezeichnung **IN** (Typ: DINT, Initialwert: 0). Diese Variable dient als Quelle für den Lesevorgang. Sie ist weder ein reiner Daten-Eingang noch ein reiner Daten-Ausgang, sondern ermöglicht den direkten Zugriff auf eine im Aufruferkontext liegende Speicherstelle. Der Baustein greift lesend auf diese Variable zu.

## Funktionsweise
Wird der Ereigniseingang **REQ** aktiviert, führt der Baustein folgende Schritte aus:
1. Der aktuelle Wert der InOut-Variable **IN** wird gelesen.
2. Dieser Wert wird in den Datenausgang **OUT** kopiert (gepuffert).
3. Anschließend wird der Ereignisausgang **CNF** gesendet, um die erfolgreiche Ausführung zu signalisieren.

Da es sich um eine einzelne Aktion handelt, ist der Baustein deterministisch und benötigt keine weiteren Zustandswechsel.

## Technische Besonderheiten
- **Direkter Speicherzugriff:** Durch die Verwendung einer InOut-Variable kann der Baustein auf eine Variable zugreifen, die außerhalb seiner eigenen Instanz liegt. Dies ermöglicht das Teilen von Daten zwischen verschiedenen Bausteinen ohne zusätzliche Eingangsverbindungen.
- **Pufferung:** Der Ausgang **OUT** hält den gelesenen Wert bis zur nächsten Aktivierung von **REQ**. Somit kann der Wert mehrfach und ohne erneute Abfrage der Quelle verwendet werden.
- **Keine Seiteneffekte:** Der Baustein verändert die InOut-Variable **IN** nicht; er liest nur ihren Wert.

## Zustandsübersicht
Der Baustein besitzt einen einzigen Zustand **REQ**. Bei Aktivierung dieses Zustands wird die Aktion des Algorithmus ausgeführt (Wert kopieren) und der Zustand verlassen, wobei **CNF** gesendet wird.

- **REQ** (Startzustand und einziger Zustand)
  - Aktion: `OUT := IN;`
  - Ausgangsereignis: **CNF**

Es gibt keine Verzweigungen, Schleifen oder Wartezeiten.

## Anwendungsszenarien
- **Puffern eines DINT-Werts:** In einer Steuerungsapplikation soll ein Messwert (z. B. von einem Sensor) nur auf Anforderung gelesen und für die weitere Verarbeitung zwischengespeichert werden.
- **Lesen geteilter Variablen:** Wenn mehrere Bausteine Zugriff auf eine gemeinsame Variable benötigen, kann **GET_DINT** den aktuellen Wert bereitstellen, ohne dass die Variable als Daten-Eingang jedes Bausteins geführt werden muss.
- **Schnittstellenentkopplung:** Trennung des Lesezeitpunkts von der eigentlichen Verarbeitung durch eine ereignisgesteuerte Pufferung.

## Vergleich mit ähnlichen Bausteinen
In der 4diac-IDE existieren analoge Bausteine für andere Datentypen (z. B. `GET_INT`, `GET_BOOL`). Der grundlegende Mechanismus ist identisch, lediglich der Datentyp unterscheidet sich. 

Im Gegensatz zu einem **MOVE**-Baustein, der einen Wert von einem Eingang zu einem Ausgang kopiert, liest **GET_DINT** den Wert aus einer InOut-Variable und puffert ihn. Dies erlaubt das Lesen von Variablen, die nicht direkt als Daten-Eingang verbunden werden können.

## Fazit
**GET_DINT** ist ein einfacher, aber nützlicher Baustein zum ereignisgesteuerten Lesen und Puffern eines DINT-Werts aus einer InOut-Variable. Seine Stärke liegt in der Möglichkeit, auf gemeinsame Variablen zuzugreifen und den gelesenen Wert ohne weitere Seiteneffekte bereitzustellen. Die klare Struktur und die geringe Komplexität machen ihn zu einem zuverlässigen Werkzeug für viele Steuerungsaufgaben.