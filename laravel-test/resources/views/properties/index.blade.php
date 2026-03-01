<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-primary leading-tight">
            {{ __('Biens Immobiliers') }}
        </h2>
    </x-slot>

    <div class="py-12">
        <div class="max-w-7xl mx-auto sm:px-6 lg:px-8">
            
            <div class="grid grid-cols-1 md:grid-cols-3 gap-6">
                
                @foreach($properties as $property)
                    <div class="bg-white overflow-hidden shadow-sm sm:rounded-lg border-t-4 border-secondary flex flex-col">
                        <div class="p-6 flex-grow">
                            <h3 class="text-lg font-bold text-gray-900">{{ $property->name }}</h3>
                            <p class="text-gray-600 mt-2 text-sm">
                                {{ Str::limit($property->description, 100) }}
                            </p>
                            
                            <div class="mt-4">
                                <span class="text-primary font-bold text-xl">
                                    {{ number_format($property->price_per_night, 2) }}€ 
                                    <span class="text-sm text-gray-500 font-normal">/ nuit</span>
                                </span>
                            </div>

                            <div class="mt-6 pt-4 border-t border-gray-100">
                                <h4 class="text-xs font-bold uppercase text-gray-400 mb-3 tracking-wider">Réserver ce bien</h4>
                                
                                @livewire('booking-manager', ['propertyId' => $property->id], key($property->id))
                            </div>
                        </div>
                    </div>
                @endforeach

            </div>

            @if($properties->isEmpty())
                <div class="text-center py-12">
                    <p class="text-gray-500 italic">Aucun bien immobilier disponible pour le moment.</p>
                </div>
            @endif

        </div>
    </div>
</x-app-layout>