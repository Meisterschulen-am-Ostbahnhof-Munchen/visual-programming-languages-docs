# AUS_TO_AUI


![AUS_TO_AUI](./AUS_TO_AUI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUS_TO_AUI** ist ein Composite-Baustein, der eine Schnittstellenumsetzung von einem AUS-Adapter (USINT-Datentyp) zu einem AUI-Adapter (UINT-Datentyp) vornimmt. Er dient als einfache Durchleitung, bei der sowohl das Ereignis als auch der Datenwert direkt vom Eingangs- zum Ausgangsadapter übertragen werden. Die implizite Typkonvertierung von USINT (8‑Bit vorzeichenlos) nach UINT (16‑Bit vorzeichenlos) erfolgt automatisch durch die Laufzeitumgebung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| E1 | Event | Ereignis-Eingang des AUS-Adapters; wird unverändert an den Ausgang weitergeleitet. |

### **Ereignis-Ausgänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| E1 | Event | Ereignis-Ausgang des AUI-Adapters; übernimmt das Ereignis vom Eingang. |

### **Daten-Eingänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| D1 | USINT | Datenwert (8‑Bit) vom AUS-Adapter; wird nach UINT konvertiert und weitergegeben. |

### **Daten-Ausgänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| D1 | UINT | Datenwert (16‑Bit) des AUI-Adapters; enthält den konvertierten USINT-Wert. |

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| adapter::types::unidirectional::AUS | AUS_IN | Socket (Eingang) | AUS-Adapter mit USINT-Daten und einem Ereignis. |
| adapter::types::unidirectional::AUI | AUI_OUT | Plug (Ausgang) | AUI-Adapter mit UINT-Daten und einem Ereignis. |

## Funktionsweise

Der Baustein arbeitet als reine Durchleitung:  
- Ein eingehendes Ereignis an `AUS_IN.E1` wird direkt an `AUI_OUT.E1` weitergegeben.  
- Der eingehende Datenwert von `AUS_IN.D1` (USINT) wird ohne zusätzliche Logik an `AUI_OUT.D1` weitergeleitet. Die Typkonvertierung von USINT nach UINT wird automatisch von der 4diac-IDE bzw. der Zielplattform ausgeführt.  

Es existieren keine internen Funktionsbausteine oder Algorithmen, die das Signal manipulieren.

## Technische Besonderheiten

- **Composite-Baustein**: Enthält keine eigenen FB-Instanzen, sondern verbindet lediglich die Adapterports direkt miteinander.  
- **Implizite Typkonvertierung**: Die Konvertierung von USINT zu UINT wird nicht explizit im FB abgebildet, sondern durch das Laufzeitsystem unterstützt. Dabei wird der 8‑Bit-Wert in den niederwertigen Teil des 16‑Bit-Worts übernommen.  
- **Unidirektionale Adapter**: Sowohl AUS als auch AUI sind als unidirektionale Adapter definiert, d.h. die Datenflüsse sind nur in eine Richtung vorgesehen.

## Zustandsübersicht

Der Baustein besitzt keine eigenen Zustände, da er keinerlei interne Logik oder Zustandsautomaten enthält. Er reagiert ausschließlich auf Eingangsereignisse und leitet diese unverzüglich weiter.

## Anwendungsszenarien

- **Systemintegration**: Wenn ein Steuerungssystem (z.B. Feldgeräte) Daten im USINT-Format liefert, ein nachgelagertes Modul aber UINT erwartet.  
- **Adapterumschaltung**: In einer SPS oder verteilten Steuerungsumgebung können Standardadapter unterschiedlicher Typen über solch einen Konvertierungsbaustein gekoppelt werden.  
- **Prototyping**: Schnelle Anpassung von Schnittstellen während der Entwicklungsphase, ohne die zugrundeliegenden Adapter zu ändern.

## Vergleich mit ähnlichen Bausteinen

- **INT_TO_UINT**: Konvertiert einen Integer-Datentyp in einen unsigned Integer – ebenfalls als Composite oder Basisbaustein realisierbar.  
- **AUS_TO_AUI** ist spezifisch auf die Adaptertypen AUS (USINT) und AUI (UINT) zugeschnitten. Andere Bausteine, wie z.B. `SINT_TO_USINT`, verwenden analoge Durchleitungen für andere Datentypen.  
- Im Gegensatz zu Bausteinen mit arithmetischer oder logischer Verarbeitung beschränkt sich dieser Baustein auf die reine Konvertierung und Ereignisweitergabe.

## Fazit

Der **AUS_TO_AUI**-Baustein ist ein schlankes Werkzeug zur Anpassung von Adapterschnittstellen zwischen USINT und UINT. Seine einfache Durchleitungsstruktur macht ihn performant und leicht verständlich. Er eignet sich besonders für Integrationsaufgaben, bei denen bestehende Komponenten mit unterschiedlichen Datenbreiten verbunden werden müssen. Aufgrund fehlender interner Logik ist er robust und benötigt keine Parametrierung.