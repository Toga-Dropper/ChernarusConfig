//#include "$CurrentDir:mpmissions/dayzOffline.chernarusplus/eAI/AI_init.c"   //to connect to your mp missions ai init.c folder

void main()
{
	/*
	  [Namalsk] CE init (offline)
	*/
	CreateHive();
	GetHive().InitOffline();

	//GetCEApi().ExportProxyData( "16000 0 16000", 20480 );  //Center of map, radius of how far to go out and find buildings.
	//EditorLoaderModule.ExportLootData = true;	

	/*
	  [Namalsk] Mission time init
	   after CE init to determine if storage mission type is outside of the required time-frame
	   currently recommended time-frame is:
		12/1 -> 12/31
		keep in mind that gameplay features are tied to the mission date (stored in the storage) and that it SHOULD remain this period!
	   while using:
		day accelerated 6 times (serverTimeAcceleration=6), resulting in an average 78 min of day-time (RL)
		night accelerated 24 times (serverNightTimeAcceleration=4), resulting in an average of 26 min of night-time (RL)
	*/
	int year, month, day, hour, minute;
	GetGame().GetWorld().GetDate( year, month, day, hour, minute );

    if ( month < 12 )
    {
    	year = 2011;
        month = 9;
        day = 5;
		
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}
//	InitDynamicPatrols();	
};

class CustomMission: MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// this piece of code is recommended otherwise event system is switched on automatically and runs from default values
		// comment this whole block if NOT using Namalsk Survival
		if ( m_EventManagerServer )
		{
			// enable/disable event system, min time between events, max time between events, max number of events at the same time
			m_EventManagerServer.OnInitServer( true, 550, 1000, 2 );
			// registering events and their probability
			m_EventManagerServer.RegisterEvent( Aurora, 0.85 );
			m_EventManagerServer.RegisterEvent( Blizzard, 0.0 );
			m_EventManagerServer.RegisterEvent( ExtremeCold, 0.0 );
			m_EventManagerServer.RegisterEvent( Snowfall, 0.0 );
			m_EventManagerServer.RegisterEvent( EVRStorm, 0.35 );
			m_EventManagerServer.RegisterEvent( HeavyFog, 0.3 );
		}
	}
		void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			int rndHlt = Math.RandomInt(55,100);
			itemEnt.SetHealth("","",rndHlt);
		}
	}
	
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}	

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand; 
		player.GetInventory().CreateInInventory("BaseballBat");    // added items	
		player.GetStatWater().Set( 900 );
		player.GetStatEnergy().Set( 1100 );		
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}

